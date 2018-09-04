#include "model.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "graphics/buffers/vertexBuffer.h"

namespace engine { namespace graphics {
	Model::Model(const char* filepath, const Texture& diffuse, const Texture& specular, const math::mat4& transform)
		: Renderable3D(transform, diffuse, specular), m_filepath(filepath) {

		parseOBJ();
	}

	void Model::parseOBJ() {
		std::ifstream stream(m_filepath);

		std::string line;
		while (getline(stream, line)) {
			if (line == "" || line[0] == '#')
				continue;

			if (line[0] == 'v') {
				if (line[1] == ' ') {
					math::vec3 pos(0, 0, 0);
					sscanf_s(line.c_str(), "%*s %f %f %f", &pos.x, &pos.y, &pos.z);
					m_positions.push_back(pos);
				}
				else if (line[1] == 't') {
					math::vec2 texCoord(0, 0);
					sscanf_s(line.c_str(), "%*s %f %f", &texCoord.x, &texCoord.y);
					m_texCoords.push_back(texCoord);
				}
				else if (line[1] == 'n') {
					math::vec3 normal(0, 0, 0);
					sscanf_s(line.c_str(), "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					m_normals.push_back(normal);
				}
			}
			else if (line[0] == 'f') {
				Face face;
				sscanf_s(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i",
					&face.positionIndices[0], &face.texCoordIndices[0], &face.normalIndices[0],
					&face.positionIndices[1], &face.texCoordIndices[1], &face.normalIndices[1],
					&face.positionIndices[2], &face.texCoordIndices[2], &face.normalIndices[2]
				);
				m_faces.push_back(face);
			}
		}
	}
} }