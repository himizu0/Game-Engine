#include "sprite.h"
#include "graphics/renderers2D/renderer2D.h"

namespace engine { namespace graphics {
	Sprite::Sprite(const math::vec2& position, const math::vec2& size, const Texture& texture)
		: Renderable2D(position, size, texture){
	}
} }