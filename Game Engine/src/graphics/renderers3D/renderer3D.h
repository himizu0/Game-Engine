#pragma once

namespace engine { namespace graphics {
	class Renderable3D;

	class Renderer3D {
		protected:
		virtual ~Renderer3D() = default;

		public:
		virtual void submit(const Renderable3D* renderable) = 0;
		virtual void flush() = 0;

		virtual void begin() {}
		virtual void end() {}
	};
} }