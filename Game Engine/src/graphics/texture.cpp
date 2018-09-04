#include <GL/glew.h>
#include "texture.h"
#include "vendor/stb_image/stb_image.h"

namespace engine { namespace graphics {
	Texture::Texture(const char* filepath)
		: m_filepath(filepath) {

		stbi_set_flip_vertically_on_load(1);
		m_buffer = stbi_load(m_filepath, &m_width, &m_height, &m_bpp, 4);

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_buffer)
			stbi_image_free(m_buffer);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::bind(unsigned int slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}

	void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}}