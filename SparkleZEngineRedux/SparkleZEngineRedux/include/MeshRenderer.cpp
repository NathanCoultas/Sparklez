#include "MeshRenderer.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "Transform.h"
#include "Component.h"
#include "Camera.h"
#include "Console.h"
#include "Material.h"
#include "GameObject.h"
#include "GraphicsCache.h"

#include <math.h>

#include <memory>

namespace sparklezEngine
{

	MeshRenderer::MeshRenderer()
	{	
		
	}

	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::Awake()
	{
		if (GetGameObject().lock()->getComponent<MeshFilter>().lock() == NULL)
		{
		  GetGameObject().lock()->addComponent<MeshFilter>();
		}
	}


	std::weak_ptr<Material> MeshRenderer::GetMaterial()
	{
		return m_Material;
	}

	void MeshRenderer::SetMaterial(std::weak_ptr<Material> _mat)
	{
		m_Material = _mat;
	}


	void MeshRenderer::SetMeshRef(std::weak_ptr<Mesh> _mesh)
	{
		if (GetGameObject().lock()->getComponent<MeshFilter>().lock())
		{
			GetGameObject().lock()->getComponent<MeshFilter>().lock()->SetMeshRef(_mesh);
		}
		else
		{
			Console::DebugMessage("MeshFilter not found");
		}
	}

	std::weak_ptr<Mesh> MeshRenderer::GetMesh()
	{
		if (GetGameObject().lock()->getComponent<MeshFilter>().lock())
		{
			return GetGameObject().lock()->getComponent<MeshFilter>().lock()->GetMesh();
		}
		else
		{
			Console::DebugMessage("MeshFilter not found");
		}

		return std::weak_ptr<Mesh>();
	}

	void MeshRenderer::SetMeshRef(std::string _filename)
	{
		if (GetGameObject().lock()->getComponent<MeshFilter>().lock())
		{
		  GetGameObject().lock()->getComponent<MeshFilter>().lock()->SetMeshRef(_filename);
		}
		else
		{
			Console::DebugMessage("MeshFilter not found");
		}
	}

	void MeshRenderer::Render()
	{
		
		std::weak_ptr<MeshFilter> l_MeshFilter = GetGameObject().lock()->getComponent<MeshFilter>();
		if (l_MeshFilter.lock() == NULL)
		{
			Console::DebugMessage("MeshFilter not attached to GameObject");
			return;
		}

		std::weak_ptr<Mesh> l_Mesh = l_MeshFilter.lock()->GetMesh();

		if (l_Mesh.lock() == NULL)
		{
			Console::DebugMessage("Mesh not attached to meshfilter");
			return;
		}

		std::weak_ptr<Transform> l_MyTrans = GetGameObject().lock()->getComponent<Transform>();

		if (l_MyTrans.lock() == NULL)
		{
			Console::DebugMessage("Transform not attached to GameObject");
			return;
		}
		
		glm::mat4 l_TransMat = glm::translate(glm::mat4(1.0f), GetTransform().lock()->GetPostion());
		glm::mat4 l_ScalMat = glm::scale(glm::mat4(1.0f), GetTransform().lock()->GetTransformScale());
		glm::mat4 l_Rotmat = glm::toMat4(glm::quat(GetTransform().lock()->GetRotation()));

		glm::mat4 l_invModelMatrix = glm::rotate(glm::mat4(1.0f), -GetTransform().lock()->GetRotation().y, glm::vec3(0, 1, 0));
		glm::mat4 l_modelMatrix = l_TransMat * l_Rotmat * l_ScalMat;
		// obtain left-handed coordinate system by multiplying a negative Z scale on ModelView matrix

		//std::weak_ptr<Material> l_material = GetMaterial();

		GraphicsCache::RenderMesh(GetMesh(), l_modelMatrix, l_invModelMatrix, GetMaterial());
		
	}
}