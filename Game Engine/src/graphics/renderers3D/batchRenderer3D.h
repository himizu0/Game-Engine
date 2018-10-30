#pragma once

#include <unordered_map>

#include "renderable3D.h"
#include "graphics/renderers3D/renderer3D.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/vertexArray.h"
#include "graphics/buffers/uniformBuffer.h"
#include "graphics/shader.h"
#include "math/math.h"

#define RENDERER3D_ELEMENTS_COUNT		1000000
#define RENDERER3D_ELEMENT_SIZE			10 * sizeof(float)
#define RENDERER3D_BUFFER_SIZE			RENDERER3D_ELEMENT_SIZE * RENDERER3D_ELEMENTS_COUNT

namespace engine { namespace graphics {
	class BatchRenderer3D : public Renderer3D{
		private:
		struct Vertex {
			math::vec3 position;
			math::vec2 texCoord;
			math::vec3 normal;
			float diffuseSlot;
			float specularSlot;
			float modelSlot;
		};

		UniformBuffer* m_ubo;
		VertexArray* m_vao;
		VertexBuffer* m_vbo;
		Vertex* m_buffer;
		unsigned int m_vertexCount;
		std::unordered_map<unsigned int, unsigned int> m_textureSlotCache;
		std::vector<math::mat4> m_models;
		std::vector<math::mat4> m_normals;

		public:
		BatchRenderer3D();
		~BatchRenderer3D();

		void submit(const Renderable3D* renderable) override;
		void flush(Shader* shader) override;
		void begin() override;
		void end() override;

		void setupUBO() const;
	};
} }