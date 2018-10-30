#include <GL/glew.h>
#include "texture.h"
#include "vendor/stb_image/stb_image.h"
#include "utils.h"

namespace engine { namespace graphics {
	Texture::Texture(const char* filepath, bool sRGB)
		: m_filepath(filepath) {

		stbi_set_flip_vertically_on_load(1);
		void* buffer = stbi_load(m_filepath, &m_width, &m_height, &m_bpp, 4);

		GLCall(glGenTextures(1, &m_textureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, sRGB ? GL_SRGB8 : GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete buffer;
	}

	Texture::~Texture() {
		GLCall(glDeleteTextures(1, &m_textureID));
	}

	void Texture::bind(unsigned int slot) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	}

	void Texture::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}}