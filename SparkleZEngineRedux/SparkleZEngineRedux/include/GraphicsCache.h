#ifndef SPARKLEZ_ENGINE_GRAPHICS_CACHE_H
#define SPARKLEZ_ENGINE_GRAPHICS_CACHE_H

#include "Mesh.h"
#include "glm\glm.hpp"
#include "glm\matrix.hpp"
#include "glm\gtx\quaternion.hpp"
#include "gl\glew.h"
#include "glm\gtx\quaternion.hpp"

#include <math.h>
#include <memory>

namespace sparklezEngine
{

  class Application;
  class Component;
  class GameObject;
  class Behaviour;
  class Material;
  class Shader;

  class GraphicsCache
  {
	friend class sparklezEngine::Application;
	friend class sparklezEngine::GameObject;
	friend class sparklezEngine::Component;
	friend class sparklezEngine::Behaviour;
	friend class sparklezEngine::Material;
	friend class sparklezEngine::Shader;
  public:
	static void SetupShaders();

	static std::weak_ptr<Mesh> GetMesh(std::string _FileName);
	static std::weak_ptr<Material> GetMaterial(std::string _FileName);
	static void RenderMesh(std::weak_ptr<Mesh> _Mesh, glm::mat4x4 _ModelMat, glm::mat4x4 _InvModelMat, std::weak_ptr<Material> _Mat);
	static unsigned int LoadTexture(std::string _filename);
  private:
	//static meshcache all functions can check
	static std::vector<std::shared_ptr<Mesh>> m_meshCache;
	static std::vector<std::shared_ptr<Material>> m_materialCache;
	static std::shared_ptr<Shader> m_DefaultModelShader;

	static std::vector<std::string> m_TextureFilePaths;

  };
}

#endif