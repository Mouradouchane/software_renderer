
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

	bool loop = true;

	std::string float_as_str = "";
	uint32_t i = start+2;
	uint32_t s = i, e = i;
	
	vec3d vertex = { 0 };
	sfloat* f_ptr = (sfloat*)(&vertex); // a pointer to "vertex.x" 
	uint8_t vertex_index = 0; // used with f_ptr to go from .x to ".y , .z"

	while (loop) {

		if (obj_buffer[i] == '\n' || obj_buffer[i] == '\0') {
			loop = false;
		}

		if (obj_buffer[i] == ' ' || !loop ) {
			e = i;
			float_as_str = std::string(obj_buffer, s, e-s);
			
			*(f_ptr + vertex_index) = (sfloat)std::atof(float_as_str.c_str());
			vertex_index += 1;

			s = e;
		}
		i += 1;
	}

	start = i+1;
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
