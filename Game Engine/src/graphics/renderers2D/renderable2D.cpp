#include "renderable2D.h"

namespace engine { namespace graphics {
	Renderable2D::Renderable2D(const math::vec2& position, const math::vec2& size, const Texture& texture)
		: m_position(position), m_size(size), m_texture(texture) {
	}
} }