#include "batchRenderer3D.h"

#include <algorithm>

namespace engine { namespace graphics {
	BatchRenderer3D::BatchRenderer3D(Shader* shader)
		: m_vertexCount(0), m_shader(shader) {

		m_vbo = new VertexBuffer(nullptr, RENDERER3D_BUFFER_SIZE, true);
		m_vbo->pushLayout<float>(3);	//position
		m_vbo->pushLayout<float>(2);	//texCoord
		m_vbo->pushLayout<float>(3);	//normal
		m_vbo->pushLayout<float>(1);	//diffuseSlot
		m_vbo->pushLayout<float>(1);	//specularSlot
		m_vbo->pushLayout<float>(1);	//modelSlot
		m_vbo->enableLayouts();
	}

	BatchRenderer3D::~BatchRenderer3D() {
		delete m_vbo;
	}


	void BatchRenderer3D::submit(const Renderable3D* renderable) {
		const std::vector<math::vec3>& positions = renderable->getPositions();
		const std::vector<math::vec2>& texCoords = renderable->getTexCoords();
		const std::vector<math::vec3>& normals = renderable->getNormals();
		const std::vector<Face>& faces = renderable->getFaces();
		const unsigned int diffuseID = renderable->getDiffuseID();
		const unsigned int specularID = renderable->getSpecularID();
		const math::mat4& transform = renderable->getTransform();

		unsigned int diffuseSlot = 0;
		unsigned int specularSlot = 0;
		unsigned int modelSlot = 0;

		if (m_textureSlotCache.find(diffuseID) != m_textureSlotCache.end() && m_textureSlotCache.find(specularID) != m_textureSlotCache.end()) {

			diffuseSlot = m_textureSlotCache[diffuseID];
			specularSlot = m_textureSlotCache[specularID];
		}
		else {
			if (m_textureSlotCache.size() >= 31) {
				end();
				flush();
				begin();
			}
			m_textureSlotCache[diffuseID] = m_textureSlotCache.size();
			m_textureSlotCache[specularID] = m_textureSlotCache.size();
			diffuseSlot = m_textureSlotCache[diffuseID];
			specularSlot = m_textureSlotCache[specularID];
		}
	
		m_models.push_back(transform);
		m_normals.push_back(math::inverseTranspose(transform));
		modelSlot = m_models.size() - 1;

		for (Face face : faces) {
			m_buffer->position = positions[face.positionIndices[0] - 1];
			m_buffer->texCoord = texCoords[face.texCoordIndices[0] - 1];
			m_buffer->normal = normals[face.normalIndices[0] - 1];
			m_buffer->diffuseSlot = (float)diffuseSlot;
			m_buffer->specularSlot = (float)specularSlot;
			m_buffer->modelSlot = (float)modelSlot;
			m_buffer++;

			m_buffer->position = positions[face.positionIndices[1] - 1];
			m_buffer->texCoord = texCoords[face.texCoordIndices[1] - 1];
			m_buffer->normal = normals[face.normalIndices[1] - 1];
			m_buffer->diffuseSlot = (float)diffuseSlot;
			m_buffer->specularSlot = (float)specularSlot;
			m_buffer->modelSlot = (float)modelSlot;
			m_buffer++;

			m_buffer->position = positions[face.positionIndices[2] - 1];
			m_buffer->texCoord = texCoords[face.texCoordIndices[2] - 1];
			m_buffer->normal = normals[face.normalIndices[2] - 1];
			m_buffer->diffuseSlot = (float)diffuseSlot;
			m_buffer->specularSlot = (float)specularSlot;
			m_buffer->modelSlot = (float)modelSlot;
			m_buffer++;

			m_vertexCount += 3;
		}
	}

	void BatchRenderer3D::flush() {
		m_shader->use();

		for (auto i = m_textureSlotCache.begin(); i != m_textureSlotCache.end(); i++) {
			glActiveTexture(GL_TEXTURE0 + i->second);
			glBindTexture(GL_TEXTURE_2D, i->first);
		}

		int textures[32];
		for (unsigned int i = 0; i < 32; i++) textures[i] = i;

		m_shader->use();
		m_shader->setUniform1iv("u_textures", textures, 32);
		m_shader->setUniformMat4fv("u_models", &m_models[0], 64);
		m_shader->setUniformMat4fv("u_normals", &m_normals[0], 64);
\

		m_vbo->bind();
		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
		printf("Draw");

		m_vertexCount = 0;
		m_textureSlotCache.clear();
		m_models.clear();
		m_normals.clear();
	}

	void BatchRenderer3D::begin() {
		m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer3D::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
} }