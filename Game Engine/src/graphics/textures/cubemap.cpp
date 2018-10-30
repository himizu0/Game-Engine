#include "cubemap.h"

#include <GL/glew.h>
#include "vendor/stb_image/stb_image.h"
#include "utils.h"

namespace engine { namespace graphics {
	Cubemap::Cubemap(const std::vector<const char*>& filepaths)
		: m_filepaths(filepaths) {

		stbi_set_flip_vertically_on_load(0);
		
		GLCall(glGenTextures(1, &m_textureID));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));

		for (unsigned int i = 0; i < 6; i++) {
			int width, height, bpp;
			m_buffer = stbi_load(m_filepaths[i], &width, &height, &bpp, 4);
			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_SRGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer));
		
			if (m_buffer)
				stbi_image_free(m_buffer);
		}

		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	}

	Cubemap::~Cubemap() {
		GLCall(glDeleteTextures(1, &m_textureID));
	}

	void Cubemap::bind() const {
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID));
	}

	void Cubemap::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}
} }