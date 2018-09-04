#pragma once

#include "renderer2D.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/indexBuffer.h"
#include "math/math.h"
#include "graphics/shader.h"

#define RENDERER2D_RENDERABLES_COUNT	10000
#define RENDERER2D_ELEMENT_SIZE			6 * sizeof(float)
#define RENDERER2D_BUFFER_SIZE			RENDERER2D_ELEMENT_SIZE * RENDERER2D_RENDERABLES_COUNT
#define RENDERER2D_INDICES_COUNT		RENDERER2D_RENDERABLES_COUNT * 6

namespace engine { namespace graphics {
	class BatchRenderer2D : public Renderer2D {
		private:
		struct VertexData {
			math::vec3 position;
			math::vec2 texCoord;
			float texSlot;
		};

		VertexBuffer* m_vbo;
		IndexBuffer* m_ibo;
		VertexData* m_buffer;
		unsigned int m_indexCount;
		bool m_bufferMapped;
		std::vector<int> m_textureIDs;

		Shader m_shader;
		
		public:
		BatchRenderer2D(const Shader& shader);
		~BatchRenderer2D();

		void submit(const Renderable2D& renderable) override;
		void flush() override;
	};
} }