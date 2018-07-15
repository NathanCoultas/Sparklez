#include "GraphicsCache.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "Console.h"

/*
Graphics Storage
*/

namespace sparklezEngine
{
  std::vector<std::shared_ptr<Mesh>> GraphicsCache::m_meshCache;
  std::vector<std::string> GraphicsCache::m_TextureFilePaths;
  std::vector<std::shared_ptr<Material>> GraphicsCache::m_materialCache;
  std::shared_ptr<Shader> GraphicsCache::m_DefaultModelShader;

  void GraphicsCache::SetupShaders()
  {
    std::shared_ptr<Shader> l_Shader(new Shader());
    l_Shader->m_ShaderID = "DefaultShader";
    l_Shader->LoadShaders("include/VertShader.txt", "include/FragShader.txt");
    m_DefaultModelShader = l_Shader;

    std::shared_ptr<Material> l_Material(new Material());
    //l_Material->m_Shader = l_Shader;
    l_Material->m_Name = "DefaultMat";
    l_Material->SetDiffuseColour(glm::vec3(1, 1, 1));
    //l_Material->SetEmissiveColour(glm::vec3(1.0f, 1.0f, 1.0f));
    //l_Material->SetSpecularColour(glm::vec3(0, 0, 0));
    l_Material->SetLightPosition(glm::vec3(0.0f, 25.0f, 0));
    l_Material->SetTexture("textures/grid.bmp");
    l_Material->SetSpecTexture("textures/grid.bmp");
    m_materialCache.push_back(l_Material);

    std::shared_ptr<Material> l_Material2(new Material());
    // l_Material2->m_Shader = l_Shader;
    l_Material2->m_Name = "DefaultMat2";
    l_Material2->SetDiffuseColour(glm::vec3(0.3f, 0.0f, 0.3f));
    l_Material2->SetEmissiveColour(glm::vec3(0.7f, 0.1f, 0.1f));
    //Material->SetSpecularColour(glm::vec3(0, 0, 0));
    //l_Material->SetLightPosition(glm::vec3(0.0f,0.0f,0));
    l_Material2->SetTexture("textures/grid.bmp");
    l_Material->SetSpecTexture("textures/grid.bmp");
    m_materialCache.push_back(l_Material2);

    std::shared_ptr<Material> l_Material3(new Material());
    // l_Material3->m_Shader = l_Shader;
    l_Material3->m_Name = "DefaultMat3";
    l_Material3->SetDiffuseColour(glm::vec3(0.3f, 0.0f, 0.3f));
    l_Material3->SetEmissiveColour(glm::vec3(0.4, 0.1, 0.4));
    //Material->SetSpecularColour(glm::vec3(0, 0, 0));
    //l_Material->SetLightPosition(glm::vec3(0.0f,0.0f,0));
    l_Material3->SetTexture("textures/grid.bmp");
    l_Material->SetSpecTexture("textures/grid.bmp");
    m_materialCache.push_back(l_Material3);

    Console::DebugMessage("Shaders Init Complete");
  }

  std::weak_ptr<Mesh> GraphicsCache::GetMesh(std::string _FileName)
  {
    for (int l_i = 0; l_i < m_meshCache.size(); l_i++)
    {
      if (m_meshCache.at(l_i)->GetFileName() == _FileName)
      {
        return m_meshCache.at(l_i);
      }
    }
    std::shared_ptr<Mesh> l_Mesh(new Mesh(_FileName));

    if (l_Mesh->GetFileName() != "NULL")
    {
      m_meshCache.push_back(l_Mesh);
      std::weak_ptr<Mesh> l_wkmesh = l_Mesh;

      return l_wkmesh;
    }

    //return null if mesh not found and cannot be created
    return std::weak_ptr<Mesh>();
  }

  std::weak_ptr<Material> GraphicsCache::GetMaterial(std::string _FileName)
  {
    for (int l_i = 0; l_i < m_materialCache.size(); l_i++)
    {
      if (m_materialCache.at(l_i)->m_Name == _FileName)
      {
        return m_materialCache.at(l_i);
      }
    }
    return std::weak_ptr<Material>();
  }

  void GraphicsCache::RenderMesh(std::weak_ptr<Mesh> _Mesh, glm::mat4x4 _ModelMat, glm::mat4x4 _InvModelMat, std::weak_ptr<Material> _Mat)
  {

    if (_Mesh.lock() == NULL)
    {
      //error
      return;
    }
    std::weak_ptr<Material> l_RenderMat;
    if (_Mat.lock() != NULL)
    {
      l_RenderMat = _Mat;
    }
    else
    {
      l_RenderMat = GetMaterial("DefaultMat");
    }

    if (l_RenderMat.lock() == NULL)
    {
      //error
      //default mat missing
      return;
    }

    glm::mat4 l_viewMat = glm::lookAt(Camera::GetMainCamera().lock()->GetTransform().lock()->GetPostion(), Camera::GetMainCamera().lock()->GetTransform().lock()->GetForwardVector() + Camera::GetMainCamera().lock()->GetTransform().lock()->GetPostion(), Camera::GetMainCamera().lock()->GetTransform().lock()->GetUpVector());
    glm::mat4 l_ProjMat = Camera::GetMainCamera().lock()->GetProjectionMatrix();

    glUseProgram(m_DefaultModelShader->m_shaderProgram);
    // Send matrices and uniforms
    glUniformMatrix4fv(m_DefaultModelShader->m_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_ModelMat));
    glUniformMatrix4fv(m_DefaultModelShader->m_shaderInvModelMatLocation, 1, GL_TRUE, glm::value_ptr(_InvModelMat));
    glUniformMatrix4fv(m_DefaultModelShader->m_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(l_viewMat));
    glUniformMatrix4fv(m_DefaultModelShader->m_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(l_ProjMat));

    //glUseProgram(m_DefaultModelShader->m_shaderProgram);

    glUniform4fv(m_DefaultModelShader->m_shaderWSLightPosLocation, 1, glm::value_ptr(l_RenderMat.lock()->m_lightPosition));
    glUniform3fv(m_DefaultModelShader->m_shaderEmissiveColLocation, 1, glm::value_ptr(l_RenderMat.lock()->m_emissiveColour));
    glUniform3fv(m_DefaultModelShader->m_shaderDiffuseColLocation, 1, glm::value_ptr(l_RenderMat.lock()->m_diffuseColour));
    glUniform3fv(m_DefaultModelShader->m_shaderSpecularColLocation, 1, glm::value_ptr(l_RenderMat.lock()->m_specularColour));

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(m_DefaultModelShader->m_shaderTex1SamplerLocation, 0);
    glUniform1i(m_DefaultModelShader->m_shaderTex2SamplerLocation, 1);
    //glUniform1i(_shaderTex3SamplerLocation, 2);
    glBindTexture(GL_TEXTURE_2D, l_RenderMat.lock()->m_texture1);
    //glBindTexture(GL_TEXTURE_2D, l_RenderMat.lock()->m_texture2);
    //glBindTexture(GL_TEXTURE_2D, _texture3);

    _Mesh.lock()->Draw();
  }

  unsigned int GraphicsCache::LoadTexture(std::string _filename)
  {

    for (int l_i = 0; l_i < m_TextureFilePaths.size(); l_i++)
    {
      if (m_TextureFilePaths.at(l_i) == _filename)
      {
        unsigned int l_rtrn = l_i + 1;
        return l_rtrn;
      }
    }

    // Load SDL surface
    SDL_Surface *image = SDL_LoadBMP(_filename.c_str());

    if (!image) // Check it worked
    {
      std::cerr << "WARNING: could not load BMP image: " << _filename << std::endl;
      return 0;
    }

    // Create OpenGL texture
    unsigned int texName = 0;
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // By default, OpenGL mag filter is linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // By default, OpenGL min filter will use mipmaps
    // We therefore either need to tell it to use linear or generate a mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // SDL loads images in BGR order
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

    //glGenerateMipmap(GL_TEXTURE_2D);
    SDL_FreeSurface(image);
    //glBindTexture(GL_TEXTURE_2D, 0);
    Console::DebugMessage(_filename + " texture loaded.");

    //m_TextureFilePaths.push_back(_filename);
    return texName;
  }
}