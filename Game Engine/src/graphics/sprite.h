#pragma once

#include "graphics/renderers2D/renderable2D.h"
#include "shader.h"

namespace engine { namespace graphics {
	class Sprite : public Renderable2D {
		public:
		Sprite(const math::vec2& position, const math::vec2& size, const Texture& texture);
	};
} }