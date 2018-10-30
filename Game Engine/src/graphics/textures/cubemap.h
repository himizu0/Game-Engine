#pragma once
#include <vector>

namespace engine { namespace graphics {
	class Cubemap {
		private:
		std::vector<const char*> m_filepaths;
		void* m_buffer;
		unsigned int m_textureID;

		public:
		Cubemap(const std::vector<const char*>& filepaths);
		~Cubemap();

		void bind() const;
		void unbind() const;
	};
} }