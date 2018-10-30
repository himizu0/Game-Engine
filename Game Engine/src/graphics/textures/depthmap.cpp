#include "depthmap.h"

#include <GL/glew.h>
#include "utils.h"

namespace engine { namespace graphics {
	Depthmap::Depthmap(int width, int height) {
		GLCall(glGenTextures(1, &m_textureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_FLOAT, nullptr));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	}

	Depthmap::~Depthmap() {
		GLCall(glDeleteTextures(1, &m_textureID));
	}

	void Depthmap::bind(unsigned int slot) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	}

	void Depthmap::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
} }