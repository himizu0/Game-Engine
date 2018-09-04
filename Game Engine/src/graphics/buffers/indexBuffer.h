#pragma once

namespace engine { namespace graphics {
	class IndexBuffer {
		private:
		unsigned int m_rendererID;

		public:
		IndexBuffer(const void* data, unsigned int size, bool dynamicDraw = false);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
	};
} }