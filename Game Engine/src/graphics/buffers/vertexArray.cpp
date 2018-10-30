#include <GL/glew.h>
#include "vertexArray.h"
#include "utils.h"

namespace engine { namespace graphics {
	VertexArray::VertexArray() {
		GLCall(glGenVertexArrays(1, &m_vertexArrayID));
	}
	
	VertexArray::~VertexArray() {
		GLCall(glDeleteVertexArrays(1, &m_vertexArrayID));
	}

	void VertexArray::bind() const {
		GLCall(glBindVertexArray(m_vertexArrayID));
	}

	void VertexArray::unbind() const {
		GLCall(glBindVertexArray(0));
	}
} }