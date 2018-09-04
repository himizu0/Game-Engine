#include <GL/glew.h>
#include "vertexArray.h"

namespace engine { namespace graphics {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_rendererID);
	}
	
	VertexArray::~VertexArray() {
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void VertexArray::bind() const {
		glBindVertexArray(m_rendererID);
	}

	void VertexArray::unbind() const {
		glBindVertexArray(0);
	}
} }