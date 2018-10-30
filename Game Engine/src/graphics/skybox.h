#pragma once

#include "textures/cubemap.h"
#include "shader.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/buffers/vertexBuffer.h"

namespace engine { namespace graphics{
	class Skybox {
		private:
		Cubemap* m_cubemap;
		Shader* m_shader;
		VertexArray* m_vao;
		VertexBuffer* m_vbo;

		void initBuffers();


		public:
		Skybox(const std::vector<const char*>& filepaths, Shader* shader);
		~Skybox();

		void draw();
	};
} }