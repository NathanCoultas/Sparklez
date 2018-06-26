#ifndef SPARKLEZ_ENGINE_COMPONENT_MESH_FILTER_H
#define SPARKLEZ_ENGINE_COMPONENT_MESH_FILTER_H
#include "Behaviour.h"
#include "BoundsBox.h"

#include <memory>
#include <string>

namespace sparklezEngine
{
	class Mesh;
	class GameObject;
	class MeshFilter : public Behaviour
	{
		friend class sparklezEngine::GameObject;
	public:
		virtual ~MeshFilter();
		
		void SetMeshRef(std::weak_ptr<Mesh> _mesh);
		void SetMeshRef(std::string _filename);
		std::weak_ptr<Mesh> GetMesh();

		void CalculateBounds();
		std::weak_ptr<BoundsBox> GetBounds();

	private:
		std::shared_ptr<BoundsBox> m_ModelBounds;
		std::weak_ptr<Mesh> m_Mesh;
	};
}

#endif