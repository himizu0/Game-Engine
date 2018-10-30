#pragma once

namespace engine { namespace graphics {
	class Depthmap {
		private:
		unsigned int m_textureID;

		public:
		Depthmap(int width, int height);
		~Depthmap();

		void bind(unsigned int slot) const;
		void unbind() const;

		inline unsigned int getID()const { return m_textureID; }
	};
} }