#include "skybox.h"

#include <GL/glew.h>
#include "utils.h"

namespace engine { namespace graphics {
	Skybox::Skybox(const std::vector<const char*>& filepaths, Shader* shader) 
		: m_shader(shader) {

		initBuffers();

		m_cubemap = new Cubemap(filepaths);
	}

	Skybox::~Skybox() {
		delete m_cubemap;
		delete m_vao;
		delete m_vbo;
	}

	void Skybox::initBuffers() {
		const float vertices[] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		m_vao = new VertexArray();
		m_vao->bind();
		m_vbo = new VertexBuffer(vertices, sizeof(vertices));
		m_vbo->pushLayout<float>(3);
		m_vbo->enableLayouts();
		m_vao->unbind();
	}

	void Skybox::draw() {
		GLCall(glDepthMask(GL_FALSE));
		m_shader->use();
		m_cubemap->bind();
		m_vao->bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		GLCall(glDepthMask(GL_TRUE));
	}
} }