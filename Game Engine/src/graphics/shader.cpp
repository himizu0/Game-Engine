#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "shader.h"
#include "math/math.h"
#include "utils.h"

namespace engine { namespace graphics {
	Shader::Shader(const char* filepath) 
		: m_filepath(filepath){

		parseShader();
		compileShader();
	}
	
	Shader::~Shader() {
		GLCall(glDeleteProgram(m_rendererID));
	}

	void Shader::parseShader() {
		std::ifstream stream(m_filepath);

		enum class ShaderType {
			NONE = -1, VERTEX = 0, GEOMETRY = 1, FRAGMENT = 2
		};

		ShaderType type = ShaderType::NONE;
		std::stringstream ss[3];
		std::string line;
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("geometry") != std::string::npos)
					type = ShaderType::GEOMETRY;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
				ss[(int)type] << line << "\n";
		}
		
		m_vertexSource = ss[0].str();
		m_geometrySource = ss[1].str();
		m_fragmentSource = ss[2].str();
	}

	void Shader::compileShader() {
		GLCall(unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER));
		const char* src = m_vertexSource.c_str();
		GLCall(glShaderSource(vertexShader, 1, &src, nullptr));
		GLCall(glCompileShader(vertexShader));
		int success;
		char infoLog[512];
		GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog));
			printf("[Shader Error] Failed to compile vertex shader: %s\n", infoLog);
		}

		/*GLCall(unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER));
		src = m_geometrySource.c_str();
		GLCall(glShaderSource(geometryShader, 1, &src, nullptr));
		GLCall(glCompileShader(geometryShader));
		GLCall(glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(geometryShader, 512, nullptr, infoLog));
			printf("[Shader Error] Failed to compile geometry shader: %s\n", infoLog);
		}*/

		GLCall(unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
		src = m_fragmentSource.c_str();
		GLCall(glShaderSource(fragmentShader, 1, &src, nullptr));
		GLCall(glCompileShader(fragmentShader));
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog));
			printf("[Shader Error] Failed to compile fragment shader: %s\n", infoLog);
		}

		GLCall(m_rendererID = glCreateProgram());
		GLCall(glAttachShader(m_rendererID, vertexShader));
		//GLCall(glAttachShader(m_rendererID, geometryShader));
		GLCall(glAttachShader(m_rendererID, fragmentShader));
		GLCall(glLinkProgram(m_rendererID));
		GLCall(glValidateProgram(m_rendererID));

		GLCall(glDeleteShader(vertexShader));
		//GLCall(glDeleteShader(geometryShader));
		GLCall(glDeleteShader(fragmentShader));
	}

	int Shader::getUniformLocation(const char* name) {
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		GLCall(int location = glGetUniformLocation(m_rendererID, name));
		if (location == -1)
			std::cout << "[OpenGl Warning] " << name << " doesn't exist" << std::endl;

		m_uniformLocationCache[name] = location;

		return location;
	}

	void Shader::use() const {
		GLCall(glUseProgram(m_rendererID));
	}

	void Shader::setUniform1i(const char* name, int value) {
		GLCall(glUniform1i(getUniformLocation(name), value));
	}

	void Shader::setUniform1iv(const char* name, int* values, unsigned int count) {
		GLCall(glUniform1iv(getUniformLocation(name), count, values));
	}

	void Shader::setUniform1f(const char* name, float value) {
		GLCall(glUniform1f(getUniformLocation(name), value));
	}

	void Shader::setUniform3f(const char* name, float v0, float v1, float v2) {
		GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
	}

	void Shader::setUniform4f(const char* name, float v0, float v1, float v2, float v3) {
		GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
	}

	void Shader::setUniformMat4f(const char* name, const math::mat4& matrix) {
		GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (const float*)&matrix));
	}

	void Shader::setUniformMat4fv(const char* name, const math::mat4* values, unsigned int count) {
		GLCall(glUniformMatrix4fv(getUniformLocation(name), count, GL_FALSE, (const float*)values));
	}
} }