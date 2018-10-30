#pragma once

namespace engine { namespace graphics {
	class Texture {
		private:
		unsigned int m_textureID;
		int m_width, m_height, m_bpp;
		const char* m_filepath;

		public:
		Texture(const char* filepath, bool sRGB = false);
		~Texture();

		void bind(unsigned int slot) const;
		void unbind() const;

		inline const unsigned int getID() const { return m_textureID; }
	};
} }