#include <GL/glew.h>
#include "vertexBuffer.h"

namespace engine { namespace graphics {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool dynamicDraw) 
		: m_stride(0) {

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_rendererID);
	}

	void VertexBuffer::enableLayouts() {
		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_elements.size(); i++) {
			const auto& element = m_elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, m_stride, (const void*)offset);
			glEnableVertexAttribArray(i);
			offset += element.getSizeofType() * element.count;
		}
	}

	template<typename T>
	void VertexBuffer::pushLayout(unsigned int count) { 
		static_assert(false); 
	}

	template<>
	void VertexBuffer::pushLayout<float>(unsigned int count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * sizeof(float);
	};

	template<>
	void VertexBuffer::pushLayout<int>(unsigned int count) {
		m_elements.push_back({ GL_INT, count, GL_FALSE });
		m_stride += count * sizeof(int);
	}
	
	void VertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void VertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
} }