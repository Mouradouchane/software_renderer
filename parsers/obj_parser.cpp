
#pragma once 

#ifndef OBJ_PARSER_CPP
#define OBJ_PARSER_CPP

#include "obj_parser.hpp"

/*
	few private function for parsing process
*/
static inline vec3d parse_to_vec3d(char* obj_buffer, uint32_t& start, uint32_t end);

static face3    make_face(char* obj_buffer, uint32_t& start, uint32_t end);
static vec3d  make_vertex(char* obj_buffer, uint32_t& start, uint32_t end);
static vec3d  make_normal(char* obj_buffer, uint32_t& start, uint32_t end);
static vec_uv make_vertex_texture(char* obj_buffer, uint32_t& start, uint32_t end);

// to check if face line is "v v v" or "v/vt/vn v/vt/vn v/vt/vn"
static bool is_simple_face(char* obj_buffer, uint32_t s, uint32_t e);

static void parse_simple_face(
	face3& face, char* obj_buffer, uint32_t* spaces , uint32_t end_of_line
);
static void parse_composite_face(
	face3& face, char* obj_buffer, uint32_t* spaces, uint32_t end_of_line
);
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
				make_face(obj_data, s, size)
			);
		}

		if (obj_data[s] == 'v') {

			if ((s < size - 1)) {

				switch (obj_data[s + 1]) {

					case ' ': { // v
						vertices->push_back(
							make_vertex(obj_data, s, size)
						);
					}
					break;

					case 't': { // vt
						s += 1;
						tvs->push_back(
							make_vertex_texture(obj_data, s, size)
						);
					}
					break;

					case 'n': { // vn
						s += 1;
						normals->push_back(
							make_normal(obj_data, s, size)
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

static inline vec3d parse_to_vec3d(char* obj_buffer, uint32_t& index, uint32_t end) {

	std::string float_as_str = "";
	index += 1;

	uint8_t  s = 0; // space index
	uint32_t spaces[3] = { NULL , NULL , NULL };

	vec3d vertex = { 0 };

	// find spaces indexs for parsing
	while (index <= end) {

		if (obj_buffer[index] == '\n' || obj_buffer[index] == '\0') {
			break;
		}

		if (obj_buffer[index] == ' ' && s < 3) {
			spaces[s] = index;
			s += 1;
		}

		index++;
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
			std::string(obj_buffer, spaces[2], index - spaces[2]).c_str()
		);
	}

	return vertex;
}

static vec3d make_vertex(char* obj_buffer, uint32_t& start , uint32_t end) {

	return parse_to_vec3d(obj_buffer, start, end);
}

static vec3d make_normal(char* obj_buffer, uint32_t& start , uint32_t end) {
	
	return parse_to_vec3d(obj_buffer, start, end);
}


static face3 make_face(char* obj_buffer, uint32_t& index , uint32_t end) {

	index += 1;

	uint32_t spaces[4] = { NULL , NULL , NULL , NULL };
	uint8_t  s = 0; // for current space index

	face3 face = face3();

	// find spaces indexs for parsing
	while (index <= end) {

		if (obj_buffer[index] == '\n' || obj_buffer[index] == '\0') {
			spaces[3] = index;
			break;
		}

		if (obj_buffer[index] == ' ' && s < 3) {
			spaces[s] = index;
			s += 1;
		}

		index++;
	}

	// if face just => f v v v
	if (is_simple_face(obj_buffer, spaces[0], spaces[1])) {
		parse_simple_face(face, obj_buffer, spaces);
	}
	else { 
	// if face => f v/vt/vn v/vt/vn v/vt/vn or v//vt//vn...
		parse_composite_face(face, obj_buffer, spaces , index);
	}

	return face;
}

static bool is_simple_face(char* obj_buffer, uint32_t s, uint32_t e) {

	while (s <= e) {

		if (obj_buffer[s] == '/') return false;
		s++;
	}

	return true;
}

static void parse_simple_face(face3& face, char* obj_buffer, uint32_t* spaces) {
	
	face.v.a = uint32_t(
		std::string(obj_buffer , spaces[0] , spaces[1] - spaces[0]).c_str()
	);

	face.v.b = uint32_t(
		std::string(obj_buffer, spaces[1], spaces[2] - spaces[1]).c_str()
	);

	face.v.c = uint32_t(
		std::string(obj_buffer, spaces[2], spaces[3] - spaces[2]).c_str()
	);

}

static void str_to_face3_value(
	char* buffer, uint32_t start, uint32_t end , face3& face, uint32_t index
) {
	
}

static void parse_composite_face(face3& face, char* obj_buffer, uint32_t* spaces, uint32_t end_of_line) {

	std::vector<std::string> parts = {
		std::string(obj_buffer, spaces[0], spaces[1] - spaces[0]),
		std::string(obj_buffer, spaces[1], spaces[2] - spaces[1]),
		std::string(obj_buffer, spaces[2], end_of_line - spaces[2])
	};
	
	for (std::string& part : parts) {

		
	}

}

static vec_uv make_vertex_texture(char* obj_buffer, uint32_t& s, uint32_t end) {
	return vec_uv();
}

#endif
