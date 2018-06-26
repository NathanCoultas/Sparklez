#ifndef SPARKLEZ_ENGINE_COMPONENT_MESH_RENDERER_H
#define SPARKLEZ_ENGINE_COMPONENT_MESH_RENDERER_H
#include "Behaviour.h"

#include "gl\glew.h"
#include "glm\gtx\quaternion.hpp"
#include <memory>
#include <vector>
#include <string>

namespace sparklezEngine
{
	class GameObject;
	class Mesh;
	class Material;
	
	class MeshRenderer : public Behaviour
	{
		friend class sparklezEngine::GameObject;
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		std::weak_ptr<Material> GetMaterial();

		void SetMaterial(std::weak_ptr<Material> _mat);
		
		void SetMeshRef(std::weak_ptr<Mesh> _mesh);
		std::weak_ptr<Mesh> GetMesh();
		void SetMeshRef(std::string _filename);
		
	private:
		virtual void Render();
		virtual void Awake();
		std::weak_ptr<Material> m_Material;

		
	};
}
#endif 
