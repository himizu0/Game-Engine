#include "batchRenderer2D.h"
#include "renderable2D.h"
#include "math/math.h"

namespace engine { namespace graphics {
	BatchRenderer2D::BatchRenderer2D(const Shader& shader) 
		: m_indexCount(0), m_bufferMapped(false), m_shader(shader){

		m_vbo = new VertexBuffer(nullptr, RENDERER2D_BUFFER_SIZE, true);
		m_vbo->pushLayout<float>(3);
		m_vbo->pushLayout<float>(2);
		m_vbo->pushLayout<float>(1);
		m_vbo->enableLayouts();

		unsigned int indices[RENDERER2D_INDICES_COUNT];
		int offset = 0;
		for (unsigned int i = 0; i < RENDERER2D_INDICES_COUNT; i+=6) {
			indices[0 + i] = 0 + offset;
			indices[1 + i] = 1 + offset;
			indices[2 + i] = 2 + offset;

			indices[3 + i] = 0 + offset;
			indices[4 + i] = 2 + offset;
			indices[5 + i] = 3 + offset;

			offset += 4;
		}
		m_ibo = new IndexBuffer(indices, sizeof(indices));
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete m_vbo;
		delete m_ibo;
	}

	void BatchRenderer2D::submit(const Renderable2D& renderable) {
		if (!m_bufferMapped) {
			m_vbo->enableLayouts();
			m_vbo->bind();
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			m_bufferMapped = true;
		}

		const math::vec2& position = renderable.getPosition();
		const math::vec2& size = renderable.getSize();
		const unsigned int textureID = renderable.getTextureID();

		float textureSlot = 0.0f;
		bool found = false;
		for(int i = 0; i < m_textureIDs.size(); i++){
			if (m_textureIDs[i] == textureID) {
				textureSlot = i;
				found = true;
				break;
			}
		}
		if (!found) {
			if (m_textureIDs.size() >= 32) {
				flush();
				m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			}
			m_textureIDs.push_back(textureID);
			textureSlot = (float)(m_textureIDs.size() - 1);
		}


		m_buffer->position = { position.x, position.y, 0 };
		m_buffer->texCoord = { 0 , 0 };
		m_buffer->texSlot = textureSlot;
		m_buffer++;
		
		m_buffer->position = { position.x, position.y + size.y, 0 };
		m_buffer->texCoord = { 0 , 1 };
		m_buffer->texSlot = textureSlot;
		m_buffer++;

		m_buffer->position = { position.x + size.x, position.y + size.y, 0 };
		m_buffer->texCoord = { 1 , 1 };
		m_buffer->texSlot = textureSlot;
		m_buffer++;

		m_buffer->position = { position.x + size.x, position.y, 0 };
		m_buffer->texCoord = { 1 , 0 };
		m_buffer->texSlot = textureSlot;
		m_buffer++;
		
		m_indexCount += 6;
	}

	void BatchRenderer2D::flush() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		m_bufferMapped = false;

		for (int i = 0; i < m_textureIDs.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureIDs[i]);
		}
		
		int textures[32];
		for (unsigned int i = 0; i < 32; i++) textures[i] = i;

		m_shader.use();
		m_shader.setUniform1iv("u_textures", textures, 32);

		m_vbo->bind();
		m_ibo->bind();
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);

		m_indexCount = 0;
		m_textureIDs.clear();
	}
} }