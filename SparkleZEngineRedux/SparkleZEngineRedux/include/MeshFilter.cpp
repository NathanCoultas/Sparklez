#include "MeshFilter.h"
#include "GraphicsCache.h"

namespace sparklezEngine
{
	MeshFilter::~MeshFilter()
	{

	}

	void MeshFilter::SetMeshRef(std::weak_ptr<Mesh> _mesh)
	{
		m_Mesh = _mesh;
		CalculateBounds();
	}

	void MeshFilter::SetMeshRef(std::string _filename)
	{
		m_Mesh = GraphicsCache::GetMesh(_filename);
		CalculateBounds();
	}

	std::weak_ptr<Mesh> MeshFilter::GetMesh()
	{
		return m_Mesh;
	}

	void MeshFilter::CalculateBounds()
	{
	
	  if (m_Mesh.lock() == NULL)
	  {
		return;
	  }
	  
	  if (m_Mesh.lock()->m_OrderedVerts.size() < 1)
	  {
		m_ModelBounds = std::shared_ptr<BoundsBox>();
		return;
	  }

	  std::vector<glm::vec3> l_Verts = m_Mesh.lock()->m_OrderedVerts;

	  float l_minX = l_Verts.at(0).x; float l_maxX = l_Verts.at(0).x;
	  float l_minY = l_Verts.at(0).y; float l_maxY = l_Verts.at(0).y;
	  float l_minZ = l_Verts.at(0).z; float l_maxZ = l_Verts.at(0).z;

	  for (int l_i = 0; l_i < l_Verts.size(); l_i++)
	  {
		if (l_Verts.at(l_i).x < l_minX)
		{
		  l_minX = l_Verts.at(l_i).x;
		}
		if (l_Verts.at(l_i).x > l_maxX)
		{
		  l_maxX = l_Verts.at(l_i).x;
		}

		if (l_Verts.at(l_i).y < l_minY)
		{
		  l_minY = l_Verts.at(l_i).y;
		}

		if (l_Verts.at(l_i).y > l_maxY)
		{
		  l_maxY = l_Verts.at(l_i).y;
		}

		if (l_Verts.at(l_i).z < l_minZ)
		{
		  l_minZ = l_Verts.at(l_i).z;
		}

		if (l_Verts.at(l_i).z > l_maxZ)
		{
		  l_maxZ = l_Verts.at(l_i).z;
		}
	  }

	  float l_midX = (l_maxX + l_minX) / 2.0f;
	  float l_midY = (l_maxY + l_minY) / 2.0f;
	  float l_midZ = (l_maxZ + l_minZ) / 2.0f;

	  float l_sizeX = l_maxX - l_minX;
	  float l_sizeY = l_maxY - l_minY;
	  float l_sizeZ = l_maxZ - l_minZ;
	  
	  m_ModelBounds = std::shared_ptr<BoundsBox>(new BoundsBox(glm::vec3(l_midX, l_midY, l_midZ), glm::vec3(l_sizeX, l_sizeY, l_sizeZ)));
	  
	}
	std::weak_ptr<BoundsBox> MeshFilter::GetBounds()
	{
	  return m_ModelBounds;
	}
}