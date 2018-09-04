#pragma once

namespace engine { namespace graphics {
	class Renderable2D;

	class Renderer2D {
		protected:
		virtual ~Renderer2D() = default;

		public:
		virtual void submit(const Renderable2D& renderable) = 0;
		virtual void flush() = 0;
	};
} }