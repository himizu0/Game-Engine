#include <GL/glew.h>
#include "indexBuffer.h"

namespace engine { namespace graphics {
	IndexBuffer::IndexBuffer(const void* data, unsigned int size, bool dynamicDraw) {
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &m_rendererID);
	}

	void IndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void IndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
} }