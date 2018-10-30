#pragma once

namespace engine { namespace graphics {
	class FrameBuffer {
		private:
		unsigned int m_bufferID;

		public:
		FrameBuffer();
		~FrameBuffer();

		void attachDepthmap(unsigned int textureID) const;

		void bind() const;
		void unbind() const;
	};
} }