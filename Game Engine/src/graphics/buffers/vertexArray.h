#pragma once

namespace engine { namespace graphics {
	class VertexArray {
		private:
		unsigned int m_rendererID;

		public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;
	};
} }