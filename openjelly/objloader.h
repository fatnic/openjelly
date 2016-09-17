#pragma once
#pragma warning(disable: 4996)

#include <iostream>
#include <vector>

#include <fstream>
#include <string>

#include <glm\glm.hpp>

class ObjLoader {
public:

	std::vector<float> data;
	float memSize;

	ObjLoader(const char* filename) {
		
		std::ifstream file(filename);
		
		if (!file) {
			std::cout << "Unable to open file: " << filename << std::endl;
			exit(1);
		}

		std::string line;

		while (std::getline(file, line)) {

			if (line.substr(0, 2) == "v ") {
				std::istringstream v(line.substr(2));
				glm::vec3 vert;
				double x, y, z;
				v >> x; v >> y; v >> z;
				vert = glm::vec3(x, y, z);
				_vertices.push_back(vert);
			}

			 else if (line.substr(0, 2) == "vt") {
				std::istringstream v(line.substr(2));
				glm::vec2 tex;
				double x, y;
				v >> x; v >> y;
				tex = glm::vec2(x, y);
				_texmap.push_back(tex);
			}

			else if (line.substr(0, 2) == "vn") {
				std::istringstream v(line.substr(2));
				glm::vec3 norm;
				double x, y, z;
				v >> x; v >> y; v >> z;
				norm = glm::vec3(x, y, z);
				_normals.push_back(norm);
			}

			if (line.substr(0, 2) == "f ") {
				int va, vb, vc;
				int ta, tb, tc;
				int na, nb, nc;

				const char* chh = line.c_str();
				std::sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &va, &ta, &na, &vb, &tb, &nb, &vc, &tc, &nc);

				data.push_back(_vertices[va-1].x);
				data.push_back(_vertices[va-1].y);
				data.push_back(_vertices[va-1].z);
				data.push_back(  _texmap[ta-1].x);
				data.push_back(  _texmap[ta-1].y);
				data.push_back( _normals[na-1].x);
				data.push_back( _normals[na-1].y);
				data.push_back( _normals[na-1].z);

				data.push_back(_vertices[vb-1].x);
				data.push_back(_vertices[vb-1].y);
				data.push_back(_vertices[vb-1].z);
				data.push_back(  _texmap[tb-1].x);
				data.push_back(  _texmap[tb-1].y);
				data.push_back( _normals[nb-1].x);
				data.push_back( _normals[nb-1].y);
				data.push_back( _normals[nb-1].z);

				data.push_back(_vertices[vc-1].x);
				data.push_back(_vertices[vc-1].y);
				data.push_back(_vertices[vc-1].z);
				data.push_back(  _texmap[tc-1].x);
				data.push_back(  _texmap[tc-1].y);
				data.push_back( _normals[nc-1].x);
				data.push_back( _normals[nc-1].y);
				data.push_back( _normals[nc-1].z);
			}

		}

		memSize = data.size() * sizeof(float);

	}

private:
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _texmap;
	std::vector<glm::vec3> _normals;
};
