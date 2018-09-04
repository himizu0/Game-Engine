#pragma once

#include <vector>

#include "graphics/texture.h"
#include "math/math.h"

namespace engine { namespace graphics {
	struct Face {
		unsigned int positionIndices[3];
		unsigned int texCoordIndices[3];
		unsigned int normalIndices[3];
	};

	class Renderable3D {
		protected:
		math::mat4 m_transform;
		std::vector<math::vec3> m_positions;
		std::vector<math::vec2> m_texCoords;
		std::vector<math::vec3> m_normals;
		std::vector<Face> m_faces;
		Texture m_diffuse;
		Texture m_specular;

		Renderable3D(const math::mat4& transform, const Texture& diffuse, const Texture& specular) 
			: m_transform(transform), m_diffuse(diffuse), m_specular(specular) {
		}

		
		public:
		virtual ~Renderable3D() = default;

		inline const math::mat4& getTransform() const { return m_transform; }
		inline const std::vector<math::vec3>& getPositions() const { return m_positions; }
		inline const std::vector<math::vec2>& getTexCoords() const { return m_texCoords; }
		inline const std::vector<math::vec3>& getNormals() const { return m_normals; }
		inline const std::vector<Face>& getFaces() const { return m_faces; }

		inline void setTransform(const math::mat4& transform) { m_transform = transform; }
		inline const unsigned int getDiffuseID() const { return m_diffuse.getID(); }
		inline const unsigned int getSpecularID() const { return m_specular.getID(); }
	};
} }