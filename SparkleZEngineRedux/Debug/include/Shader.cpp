#include "Shader.h"
#include "sdl\include\SDL.h"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace sparklezEngine
{
  Shader::Shader()
  {
    m_shaderModelMatLocation = 0;
    m_shaderViewMatLocation = 0;
    m_shaderProjMatLocation = 0;

    m_shaderDiffuseColLocation = 0;
    m_shaderEmissiveColLocation = 0;
    m_shaderWSLightPosLocation = 0;
    m_shaderSpecularColLocation = 0;

    m_shaderTex1SamplerLocation = 0;
    m_shaderTex2SamplerLocation = 0;
    m_shaderTex3SamplerLocation = 0;
  }
  bool Shader::LoadShaders(std::string _vertshaderFilename, std::string _fragshaderFilename)
	{

		std::ifstream l_vertFile(_vertshaderFilename);
		char *vShaderText = NULL;

		if (l_vertFile.is_open())
		{
			// Find out how many characters are in the file
			l_vertFile.seekg(0, l_vertFile.end);
			int length = (int)l_vertFile.tellg();
			l_vertFile.seekg(0, l_vertFile.beg);

			// Create our buffer
			vShaderText = new char[length];

			// Transfer data from file to buffer
			l_vertFile.read(vShaderText, length);

			// Check it reached the end of the file
			if (!l_vertFile.eof())
			{
				l_vertFile.close();
				std::cerr << "WARNING: could not read vertex shader from file: " << _vertshaderFilename << std::endl;
				return false;
			}

			// Find out how many characters were actually read
			length = (int)l_vertFile.gcount();

			// Needs to be NULL-terminated
			vShaderText[length - 1] = 0;

			l_vertFile.close();
		}
		else
		{
			std::cerr << "WARNING: could not open vertex shader from file: " << _vertshaderFilename << std::endl;
			return false;
		}


		std::ifstream l_fragFile(_fragshaderFilename);
		char *fShaderText = NULL;

		if (l_fragFile.is_open())
		{
			// Find out how many characters are in the file
			l_fragFile.seekg(0, l_fragFile.end);
			int length = (int)l_fragFile.tellg();
			l_fragFile.seekg(0, l_fragFile.beg);

			// Create our buffer
			fShaderText = new char[length];

			// Transfer data from file to buffer
			l_fragFile.read(fShaderText, length);

			// Check it reached the end of the file
			if (!l_fragFile.eof())
			{
				l_fragFile.close();
				std::cerr << "WARNING: could not read fragment shader from file: " << _fragshaderFilename << std::endl;
				return false;
			}

			// Find out how many characters were actually read
			length = (int)l_fragFile.gcount();

			// Needs to be NULL-terminated
			fShaderText[length - 1] = 0;

			l_fragFile.close();
		}
		else
		{
			std::cerr << "WARNING: could not open fragment shader from file: " << _fragshaderFilename << std::endl;
			return false;
		}



		// The 'program' stores the shaders
		m_shaderProgram = glCreateProgram();

		// Create the vertex shader
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		// Give GL the source for it
		glShaderSource(vShader, 1, &vShaderText, NULL);
		// Delete buffer
		delete[] vShaderText;
		// Compile the shader
		glCompileShader(vShader);
		// Check it compiled and give useful output if it didn't work!
		if (!CheckShaderCompiled(vShader))
		{
			std::cerr << "ERROR: failed to compile vertex shader" << std::endl;
			return false;
		}
		// This links the shader to the program
		glAttachShader(m_shaderProgram, vShader);

		// Same for the fragment shader
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fShaderText, NULL);
		// Delete buffer
		delete[] fShaderText;
		glCompileShader(fShader);
		if (!CheckShaderCompiled(fShader))
		{
			std::cerr << "ERROR: failed to compile fragment shader" << std::endl;
			return false;
		}
		glAttachShader(m_shaderProgram, fShader);

		// This makes sure the vertex and fragment shaders connect together
		glLinkProgram(m_shaderProgram);
		// Check this worked
		GLint linked;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(m_shaderProgram, len, &len, log);
			std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
			delete[] log;

			return false;
		}


		// We will define matrices which we will send to the shader
		// To do this we need to retrieve the locations of the shader's matrix uniform variables
		glUseProgram(m_shaderProgram);
		m_shaderModelMatLocation = glGetUniformLocation(m_shaderProgram, "modelMat");
		m_shaderInvModelMatLocation = glGetUniformLocation(m_shaderProgram, "invModelMat");
		m_shaderViewMatLocation = glGetUniformLocation(m_shaderProgram, "viewMat");
		m_shaderProjMatLocation = glGetUniformLocation(m_shaderProgram, "projMat");

		m_shaderDiffuseColLocation = glGetUniformLocation(m_shaderProgram, "diffuseColour");
		m_shaderEmissiveColLocation = glGetUniformLocation(m_shaderProgram, "emissiveColour");
		m_shaderSpecularColLocation = glGetUniformLocation(m_shaderProgram, "specularColour");
		m_shaderWSLightPosLocation = glGetUniformLocation(m_shaderProgram, "worldSpaceLightPos");

		m_shaderTex1SamplerLocation = glGetUniformLocation(m_shaderProgram, "tex1");
		m_shaderTex2SamplerLocation = glGetUniformLocation(m_shaderProgram, "spec2");
		//_shaderTex3SamplerLocation = glGetUniformLocation(_shaderProgram, "amb3");

		return true;
	}

	bool Shader::CheckShaderCompiled(GLint _shader)
	{
		GLint l_compiled;
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &l_compiled);
		if (!l_compiled)
		{
			GLsizei len;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &len);

			// OpenGL will store an error message as a string that we can retrieve and print
			GLchar* l_log = new GLchar[len + 1];
			glGetShaderInfoLog(_shader, len, &len, l_log);
			std::cerr << "ERROR: Shader compilation failed: " << l_log << std::endl;
			delete[] l_log;

			return false;
		}
		return true;
	}
}