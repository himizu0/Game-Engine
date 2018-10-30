#include "uniformBuffer.h"

#include <GL/glew.h>
#include "utils.h"

namespace engine { namespace graphics {
	UniformBuffer::UniformBuffer(unsigned int size, unsigned int base, const void* data, bool dynamicDraw){
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
		glBufferData(GL_UNIFORM_BUFFER, size, data, dynamicDraw ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, base, m_bufferID);
	}

	UniformBuffer::~UniformBuffer(){
		glDeleteBuffers(1, &m_bufferID);
	}

	void UniformBuffer::subData(unsigned int size, const void* data, unsigned int offset) const{
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}

	void UniformBuffer::bind() const{
		glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	}

	void UniformBuffer::unbind() const{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
} }