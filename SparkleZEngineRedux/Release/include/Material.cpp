#include "Material.h"
#include "sdl\include\SDL.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Console.h"
#include "GraphicsCache.h"
#include <string>
#include <iostream>
#include <fstream>

namespace sparklezEngine
{
  Material::Material()
  {
    m_texture1 = 0;
  }
  void Material::SetShader(std::weak_ptr<Shader> _shader)
  {
      m_Shader = _shader;
  }
  void Material::SetEmissiveColour(glm::vec3 _input)
  {
     m_emissiveColour = _input;
  }
  void Material::SetDiffuseColour(glm::vec3 _input)
  {
     m_diffuseColour = _input;
  }
  void Material::SetSpecularColour(glm::vec3 _input)
  {
     m_specularColour = _input;
  }
  void Material::SetLightPosition(glm::vec3 _input)
  {
     m_lightPosition = _input;
  }
  void Material::SetLightItentsity(glm::vec3 _input)
  {
     m_LightIntent = _input;
  }

  bool Material::SetTexture(std::string _filename)
  {
     m_texture1 = GraphicsCache::LoadTexture(_filename);
     return m_texture1 > 0;
  }
  bool Material::SetSpecTexture(std::string _filename)
  {
     m_texture2 = GraphicsCache::LoadTexture(_filename);
     return m_texture2 > 1;
  }
  bool Material::SetIluTexture(std::string _filename)
  {
     m_texture3 = GraphicsCache::LoadTexture(_filename);
     return m_texture3 > 2;
  }
}