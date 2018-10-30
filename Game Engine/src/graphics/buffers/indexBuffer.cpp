#include <GL/glew.h>
#include "indexBuffer.h"
#include "utils.h"

namespace engine { namespace graphics {
	IndexBuffer::IndexBuffer(const void* data, unsigned int size, bool dynamicDraw) {
		GLCall(glGenBuffers(1, &m_rendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GLCall(glDeleteBuffers(1, &m_rendererID));
	}

	void IndexBuffer::bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}

	void IndexBuffer::unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
} }