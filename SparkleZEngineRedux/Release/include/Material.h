#ifndef SPARKLEZ_ENGINE_COMPONENT_MATERIAL_H
#define SPARKLEZ_ENGINE_COMPONENT_MATERIAL_H
#include <memory>
#include "Shader.h"

namespace sparklezEngine
{
	class GameObject;
	class GraphicsCache;
	class Material
	{
		friend class sparklezEngine::GameObject;
		friend class sparklezEngine::GraphicsCache;
	public:

    Material();

		void SetShader(std::weak_ptr<Shader> _shader);
		// For setting material properties
		void SetEmissiveColour(glm::vec3 _input);
		void SetDiffuseColour(glm::vec3 _input);
		void SetSpecularColour(glm::vec3 _input);
		// Set light position in world space
		void SetLightPosition(glm::vec3 _input);
		void SetLightItentsity(glm::vec3 _input);

		bool SetTexture(std::string _filename);
		bool SetSpecTexture(std::string _filename);
		bool SetIluTexture(std::string _filename);


	private:

    std::string m_Name;
    //mat props
    glm::vec3 m_emissiveColour, m_diffuseColour, m_specularColour;
    glm::vec3 m_lightPosition, m_LightIntent;
    std::weak_ptr<Shader> m_Shader;

    //Loads a .bmp from file

    // OpenGL handle for the texture
    unsigned int m_texture1; //texture
    unsigned int m_texture2; //specText
    unsigned int m_texture3; //test texture
	};

}
#endif