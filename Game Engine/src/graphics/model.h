#pragma once

#include "graphics/renderers3D/renderable3D.h"

namespace engine { namespace graphics {
	class Model : public Renderable3D{
		private:
		const char* m_filepath;

		void parseOBJ();

		public:
		Model(const char* filepath, const Texture& diffuse, const Texture& specular, const math::mat4& transform = math::mat4::identity());
	};
} }