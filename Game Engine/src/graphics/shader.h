#pragma once

#include <unordered_map>

namespace engine { namespace math {
	struct mat4;
} }

namespace engine { namespace graphics {
	class Shader {
		private:
		unsigned int m_rendererID;
		const char* m_filepath;
		std::string m_vertexSource;
		std::string m_geometrySource;
		std::string m_fragmentSource;
		std::unordered_map<const char*, int> m_uniformLocationCache;
		
		void parseShader();
		void compileShader();

		int getUniformLocation(const char* name);

		public:
		Shader(const char* filepath);
		~Shader();

		void use() const;

		void setUniform1i(const char* name, int value);
		void setUniform1iv(const char* name, int* values, unsigned int count);
		void setUniform1f(const char* name, float value);
		void setUniform3f(const char* name, float v0, float v1, float v2);
		void setUniform4f(const char* name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const char* name, const math::mat4& matrix);
		void setUniformMat4fv(const char* name, const math::mat4* values, unsigned int count);
	};
} }