#include "frameBuffer.h"

#include <GL/glew.h>
#include "utils.h"

namespace engine { namespace graphics {
	FrameBuffer::FrameBuffer() {
		GLCall(glGenFramebuffers(1, &m_bufferID));
	}

	FrameBuffer::~FrameBuffer() {
		GLCall(glDeleteFramebuffers(1, &m_bufferID));
	}

	void FrameBuffer::attachDepthmap(unsigned int textureID) const {
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureID, 0));
		GLCall(glDrawBuffer(GL_NONE));
		GLCall(glReadBuffer(GL_NONE));
	}

	void FrameBuffer::bind() const {
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_bufferID));
	}

	void FrameBuffer::unbind() const {
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}}