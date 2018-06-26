#ifndef SPARKLEZ_ENGINE_SHADER_H
#define SPARKLEZ_ENGINE_SHADER_H
#include <memory>
#include <string>
#include "glm\glm.hpp"
#include "gl\glew.h"

namespace sparklezEngine
{
	class GameObject;
	class GraphicsCache;
	class Material;

	class Shader
	{
		friend class sparklezEngine::GameObject;
		friend class sparklezEngine::GraphicsCache;
		friend class sparklezEngine::Material;
	public:
    Shader();

		bool LoadShaders(std::string _vertshaderFilename, std::string _fragshaderFilename);
	private:
      std::string m_ShaderID;
		bool CheckShaderCompiled(GLint _shader);

		// The OpenGL shader program handle
		int m_shaderProgram;

		// Locations of Uniforms in the vertex shader
		int m_shaderModelMatLocation;
		int m_shaderInvModelMatLocation;
		int m_shaderViewMatLocation;
		int m_shaderProjMatLocation;

		// Location of Uniforms in the fragment shader
		int m_shaderDiffuseColLocation, m_shaderEmissiveColLocation, m_shaderSpecularColLocation;
		int m_shaderWSLightPosLocation;
		int m_shaderTex1SamplerLocation, m_shaderTex2SamplerLocation, m_shaderTex3SamplerLocation;
	};

}
#endif