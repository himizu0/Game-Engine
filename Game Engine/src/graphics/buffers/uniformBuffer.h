#pragma once

namespace engine { namespace graphics {
	class UniformBuffer {
		private:
		unsigned int m_bufferID;

		public:
		UniformBuffer(unsigned int size, unsigned int base, const void* data = nullptr, bool dynamicDraw = false);
		~UniformBuffer();

		void subData(unsigned int size, const void* data, unsigned int offset) const;

		void bind() const;
		void unbind() const;
	};
} }