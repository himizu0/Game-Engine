#pragma once

#include <GL/glew.h>
#include <vector>

namespace engine { namespace graphics {
	class VertexBuffer {
		private:
		struct VertexBufferElement {
			unsigned int type;
			unsigned int count;
			unsigned char normalized;

			inline unsigned int getSizeofType() const {
				if (type == GL_FLOAT) return sizeof(float);
				else __debugbreak;
			}
		};

		unsigned int m_rendererID;
		std::vector<VertexBufferElement> m_elements;
		unsigned int m_stride;


		public:
		VertexBuffer(const void* data, unsigned int size, bool dynamicDraw = false);
		~VertexBuffer();

		template<typename T>
		void pushLayout(unsigned int count);

		void enableLayouts();

		void bind() const;
		void unbind() const;
	};
} }