#pragma once

#include "graphics/texture.h"
#include "math/math.h"

namespace engine { namespace graphics {
	class Renderer2D;

	class Renderable2D {
		protected:
		math::vec2 m_position;
		math::vec2 m_size;
		Texture m_texture;


		public:
		Renderable2D(const math::vec2& position, const math::vec2& size, const Texture& texture);
		virtual ~Renderable2D() = default;

		inline const math::vec2& getPosition() const { return m_position; }
		inline const math::vec2& getSize() const { return m_size; }
		inline const unsigned int getTextureID() const { return m_texture.getID(); }
	};
} }