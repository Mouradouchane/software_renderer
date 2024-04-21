
#pragma once 

#ifndef OBJ_PARSER_CPP
#define OBJ_PARSER_CPP

#include "obj_parser.hpp"


/*
	few private function for parsing process
*/
vec3d parse_vertex(char* obj_buffer, uint32_t& start, uint32_t end);
face3 parse_face(char* obj_buffer, uint32_t& s, uint32_t end);
vec3d parse_normal(char* obj_buffer, uint32_t& s, uint32_t end);
vec_uv parse_texture_vertex(char* obj_buffer, uint32_t& s, uint32_t end);
// ==========================================


/*
	=====================================
	==== namespace parser function ======
	=====================================
*/

mesh* parser::obj(char* obj_data, uint32_t size) {

	mesh* obj = new mesh();

	std::vector<vec_uv>* tvs      = new std::vector<vec_uv>();
	std::vector<vec3d>*  vertices = new std::vector<vec3d>();
	std::vector<vec3d>*  normals  = new std::vector<vec3d>();
	std::vector<face3>*  faces    = new std::vector<face3>();

	for (uint32_t s = 0; s < size; s++) {

		if (obj_data[s] == 'f') {
			faces->push_back(
				parse_face(obj_data, s, size)
			);
		}

		if (obj_data[s] == 'v') {

			if ((s < size - 1)) {

				switch (obj_data[s + 1]) {

				case ' ': { // v
					vertices->push_back(
						parse_vertex(obj_data, s, size)
					);
				}
						break;

				case 't': { // vt
					tvs->push_back(
						parse_texture_vertex(obj_data, s, size)
					);
				}
						break;

				case 'n': { // vn
					normals->push_back(
						parse_normal(obj_data, s, size)
					);
				}
						break;

				}

			}

		}

	}

	return obj;
}


/*
	=====================================
	===== private parsing function ======
	=====================================
*/

vec3d parse_vertex(char* obj_buffer, uint32_t& start , uint32_t end) {

	std::string float_as_str = "";
	uint32_t i = start+1;
	
	uint32_t spaces[3] = { NULL , NULL , NULL };
	uint8_t s = 0;

	vec3d vertex = { 0 };

	// find spaces indexs for parsing
	while (i <= end) {

		if (obj_buffer[i] == '\n' || obj_buffer[i] == '\0') {
			break;
		}

		if (obj_buffer[i] == ' ' && s < 3) {
			spaces[s] = i;
			s += 1;
		}

		i += 1;
	}

	// parse x 
	if (spaces[0] != NULL && spaces[1] != NULL) {
		vertex.x = (sfloat)std::stod(
			std::string(obj_buffer, spaces[0], spaces[1] - spaces[0]).c_str()
		);
	}
	// parse y
	if (spaces[1] != NULL && spaces[2] != NULL) {
		vertex.y = (sfloat)std::stod(
			std::string(obj_buffer, spaces[1], spaces[2] - spaces[1]).c_str()
		);
	}
	// parse z
	if (spaces[2] != NULL) {
		vertex.z = (sfloat)std::stod(
			std::string(obj_buffer, spaces[2], i - spaces[2]).c_str()
		);
	}

	start = i;
	return vertex;
}

face3 parse_face(char* obj_buffer, uint32_t& s , uint32_t end) {
	return face3();
}

vec3d parse_normal(char* obj_buffer, uint32_t& s , uint32_t end) {
	return vec3d();
}

vec_uv parse_texture_vertex(char* obj_buffer, uint32_t& s, uint32_t end) {
	return vec_uv();
}

#endif
