
#pragma once 

#ifndef OBJ_PARSER_CPP
#define OBJ_PARSER_CPP

#include "obj_parser.hpp"

/*
	few private function for parsing process
*/
static inline vec3d parse_to_vec3d(char* obj_buffer, uint32_t& start, uint32_t end);

static vec3d  make_vertex(char* obj_buffer, uint32_t& start, uint32_t end);
static vec3d  make_normal(char* obj_buffer, uint32_t& start, uint32_t end);
static face3  make_face(  char* obj_buffer, uint32_t& start, uint32_t end);
static vec_uv make_vertex_texture(char* obj_buffer, uint32_t& start, uint32_t end);

// to check if face line is "v v v" or "v/vt/vn v/vt/vn v/vt/vn"
static bool is_simple_face(char* obj_buffer, uint32_t s, uint32_t e);

static void make_face_from_simple_str(
	face3& face, char* obj_buffer, uint32_t* spaces
);
static void make_face_from_composite_str(
	face3& face, char* obj_buffer, uint32_t* spaces
);
static void extract_values(
	face3& face, char* obj_buffer, char op, uint32_t start, uint32_t end
);
// ==========================================


/*
	=====================================
	===== namespace parser function =====
	=====================================
*/

mesh* parser::obj(char* obj_data, uint32_t size) {

mesh* obj = new mesh();

for (uint32_t s = 0; s < size; s++) {

	if (obj_data[s] == '#') {
		// skip comment
		while (obj_data[s] != '\n') s++;
	}

	if (obj_data[s] == 'f') {
		obj->f.push_back(
			make_face(obj_data, s, size)
		);
	}

	if (obj_data[s] == 'v') {

		if ((s < size - 1)) {

			switch (obj_data[s + 1]) {

			case ' ': { // v
				obj->v.push_back(
					make_vertex(obj_data, s, size)
				);
			}
			break;

			case 't': { // vt
				s += 1;
				obj->vt.push_back(
					make_vertex_texture(obj_data, s, size)
				);
			}
			break;

			case 'n': { // vn
				s += 1;
				obj->n.push_back(
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

		if (obj_buffer[index] == '\n' || obj_buffer[index] == '\0' || index == end) {
			spaces[3] = index;
			break;
		}

		if (obj_buffer[index] == ' ' && s < 3) {
			spaces[s] = index;
			s += 1;
		}

		index++;
	}

	if (spaces[0] == spaces[1] == spaces[2] == spaces[3]) return face;

	// if face just => f v v v
	if ( is_simple_face(obj_buffer, spaces[0], spaces[1]) ) {
		make_face_from_simple_str(face, obj_buffer, spaces);
	}
	else { 
		// if face => f v/vt/vn v/vt/vn v/vt/vn or v//vt//vn...
		make_face_from_composite_str(face, obj_buffer, spaces);
	}

	return face;
}

static bool is_simple_face(
	char* obj_buffer, uint32_t s, uint32_t e
) {
	
	if (s == e) return false;

	while (s <= e) {

		if (obj_buffer[s] == '/') return false;
		s++;
	}

	return true;
}

static void make_face_from_simple_str(
	face3& face, char* obj_buffer, uint32_t* spaces
) {
	
	face.a.v = uint32_t(
		std::stoul( std::string(obj_buffer + spaces[0], obj_buffer + spaces[1]) ) -1
	);

	face.b.v = uint32_t(
		std::stoul( std::string(obj_buffer + spaces[1], obj_buffer + spaces[2]) ) -1
	);

	face.c.v = uint32_t(
		std::stoul( std::string(obj_buffer + spaces[2], obj_buffer + spaces[3]) ) -1
	);

}

static void extract_values(
	face3& face, char* obj_buffer, char op, uint32_t s, uint32_t e
) {

	uint32_t spaces[4] = { s , NULL , NULL , e };
	uint8_t i = 1;

	while (s <= e) {
		
		if (obj_buffer[s] == '/') {
			spaces[i] = s+1;
			i++;
		}

		s++;
	}

	if (i == 3) {

		face[op].v = uint32_t(
			std::stoul(std::string(obj_buffer + spaces[0], obj_buffer + spaces[1])) -1
		);

		// in case not ==> v//n
		if (spaces[1] + 1 != spaces[2]) {
			face[op].vt = uint32_t(
				std::stoul(std::string(obj_buffer + spaces[1], obj_buffer + spaces[2])) -1
			);
		}

		face[op].n = uint32_t(
			std::stoul(std::string(obj_buffer + spaces[2], obj_buffer + spaces[3])) -1
		);

	}
	else {

		face[op].v = uint32_t(
			std::stoul(std::string(obj_buffer + spaces[0], obj_buffer + spaces[1])) -1
		);
		
		face[op].vt = uint32_t(
			std::stoul(std::string(obj_buffer + spaces[1], obj_buffer + spaces[3])) -1
		);
	}

}

static void make_face_from_composite_str(
	face3& face, char* obj_buffer, uint32_t* spaces
) {

	if (spaces[0] != NULL && spaces[0] != spaces[1]) {
		extract_values(face, obj_buffer, 'a', spaces[0], spaces[1]);
	}

	if (spaces[1] != NULL && spaces[1] != spaces[2]) {
		extract_values(face, obj_buffer, 'b', spaces[1], spaces[2]);
	}

	if (spaces[2] != NULL && spaces[2] != spaces[3]) {
		extract_values(face, obj_buffer, 'c', spaces[2], spaces[3]);
	}

}

static vec_uv make_vertex_texture(char* obj_buffer, uint32_t& s, uint32_t end) {
	
	vec_uv coordinates = { 0 };
	
	s++;
	uint32_t spaces[4] = { s , NULL , NULL , NULL };
	uint8_t  i = 1;
	s++; 

	while ( s <= end ) {

		if ( obj_buffer[s] == '\n' || obj_buffer[s] == '\0') {
			spaces[3] = s;
			break;
		}

		if (obj_buffer[s] == ' ' && i < 3) {
			spaces[i] = s;
			i++;
		}

		s++;
	}
	
	coordinates.u = sfloat(
		std::stof( std::string(obj_buffer + spaces[0], obj_buffer + spaces[1]) )
	);

	coordinates.v = sfloat(
		std::stof( std::string(obj_buffer + spaces[1], obj_buffer + spaces[3]) )
	);

	return coordinates;
}

#endif

