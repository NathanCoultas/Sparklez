#ifndef SPARKLEZ_ENGINE_MESH_H
#define SPARKLEZ_ENGINE_MESH_H

#include "glm\glm.hpp"
#include "sdl\include\SDL.h"
#include "gl\glew.h"

#include <string>
#include <vector>
#include <memory>

namespace sparklezEngine
{
	class GameObject;
	class MeshFilter;
	class MeshRenderer;
	class GraphicsCache;

	class Mesh
	{
		friend class sparklezEngine::GameObject;
		friend class sparklezEngine::MeshFilter;
		friend class sparklezEngine::MeshRenderer;
		friend class sparklezEngine::GraphicsCache;
	public:
		Mesh(std::string _FileName);
		Mesh();
		~Mesh();
		
		void LoadObj(std::string _Filename);
      void Draw();

		GLuint GetVAO();
		std::vector<glm::vec3> GetVerts();
		std::string GetFileName();

	private:
		// OpenGL Vertex Array Object
		GLuint m_VAO;
		// Number of vertices in the mesh
		unsigned int m_numVertices;
		//verts of the loaded mesh in order, / 3 to get tris
		std::vector<glm::vec3> m_OrderedVerts;
		std::vector<glm::vec3> m_OrderedNormals;
		std::vector<glm::vec2> m_OrderedUV;

		//filename of loadedmesh
		std::string m_MeshFileName;
	
	};
}
#endif 