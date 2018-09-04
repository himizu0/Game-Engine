#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "shader.h"
#include "math/math.h"

namespace engine { namespace graphics {
	Shader::Shader(const char* filepath) 
		: m_filepath(filepath){

		parseShader();
		compileShader();
	}
	
	Shader::~Shader() {
		glDeleteProgram(m_rendererID);
	}

	void Shader::parseShader() {
		std::ifstream stream(m_filepath);

		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		ShaderType type = ShaderType::NONE;
		std::stringstream ss[2];
		std::string line;
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else
				ss[(int)type] << line << "\n";
		}
		
		m_vertexSource = ss[0].str();
		m_fragmentSource = ss[1].str();
	}

	void Shader::compileShader() {
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* src = m_vertexSource.c_str();
		glShaderSource(vertexShader, 1, &src, nullptr);
		glCompileShader(vertexShader);
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			printf("[Shader Error] Failed to compile vertex shader: %s\n", infoLog);
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		src = m_fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &src, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			printf("[Shader Error] Failed to compile fragment shader: %s\n", infoLog);
		}

		m_rendererID = glCreateProgram();
		glAttachShader(m_rendererID, vertexShader);
		glAttachShader(m_rendererID, fragmentShader);
		glLinkProgram(m_rendererID);
		glValidateProgram(m_rendererID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	int Shader::getUniformLocation(const char* name) {
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int location = glGetUniformLocation(m_rendererID, name);
		if (location == -1)
			std::cout << "[OpenGl Warning] " << name << " doesn't exist" << std::endl;

		m_uniformLocationCache[name] = location;

		return location;
	}

	void Shader::use() const {
		glUseProgram(m_rendererID);
	}

	void Shader::setUniform1i(const char* name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform1iv(const char* name, int* values, unsigned int count) {
		glUniform1iv(getUniformLocation(name), count, values);
	}

	void Shader::setUniform1f(const char* name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform3f(const char* name, float v0, float v1, float v2) {
		glUniform3f(getUniformLocation(name), v0, v1, v2);
	}

	void Shader::setUniformMat4f(const char* name, const math::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, (const float*)&matrix);
	}

	void Shader::setUniformMat4fv(const char* name, math::mat4* values, unsigned int count) {
		glUniformMatrix4fv(getUniformLocation(name), count, GL_FALSE, (const float*)&values);
	}
} }