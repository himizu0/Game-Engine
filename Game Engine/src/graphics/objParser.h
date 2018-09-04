#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "math/math.h"

namespace engine { namespace graphics {
	struct Vertex {
		math::vec3 position;
		math::vec2 texCoord;
		math::vec3 normal;
	};

	struct Face {
		unsigned int positions[3];
		unsigned int texCoords[3];
		unsigned int normals[3];
	};

	struct Model {
		std::vector<math::vec3> positions;
		std::vector<math::vec2> texCoords;
		std::vector<math::vec3> normals;
		std::vector<Face> faces;
	};

	Model parseOBJ(const char* filepath) {
		std::ifstream stream(filepath);

		std::vector<math::vec3> positions;
		std::vector<math::vec2> texCoords;
		std::vector<math::vec3> normals;
		std::vector<Face> faces;

		std::stringstream ss;
		std::string line;
		while (getline(stream, line)) {
			if (line == "" || line[0] == '#') 
				continue;

			if (line[0] == 'v') {
				if (line[1] == ' ') {
					math::vec3 pos(0, 0, 0);
					sscanf_s(line.c_str(), "%*s %f %f %f", &pos.x, &pos.y, &pos.z);
					positions.push_back(pos);
				}
				else if (line[1] == 't') {
					math::vec2 texCoord(0, 0);
					sscanf_s(line.c_str(), "%*s %f %f", &texCoord.x, &texCoord.y);
					texCoords.push_back(texCoord);
				}
				else if (line[1] == 'n') {
					math::vec3 normal(0, 0, 0);
					sscanf_s(line.c_str(), "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					normals.push_back(normal);
				}
			}
			else if (line[0] == 'f') {
				Face face;
				sscanf_s(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i",
					&face.positions[0], &face.positions[1], &face.positions[2],
					&face.texCoords[0], &face.texCoords[1], &face.texCoords[2],
					&face.normals[0], &face.normals[1], &face.normals[2]
				);
				faces.push_back(face);
			}
		}
		return { positions, texCoords, normals, faces };
	}
} }