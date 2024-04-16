
#pragma once 

#ifndef OBJ_PARSER_CPP
#define OBJ_PARSER_CPP

#include "obj_parser.hpp"

vec3d parse_vertex(char* file_data, uint32_t s , uint32_t e) {

}

vec3d parse_normal(char* file_data, uint32_t s, uint32_t e) {

}

face3 parse_face(char* file_data, uint32_t s, uint32_t e) {

}

texture_vertex parse_texture_vertex(char* file_data, uint32_t s, uint32_t e) {

}

mesh* parse_obj(char* file_data, uint32_t size) {

	mesh* obj = new mesh();
	
	std::vector<texture_vertex>* tvs = new std::vector<texture_vertex>();
	std::vector<vec3d>* vertices = new std::vector<vec3d>();
	std::vector<vec3d>* normals = new std::vector<vec3d>();
	std::vector<face3>* faces = new std::vector<face3>();
	
	for (uint32_t s = 0 , e = 0; s < size; s++) {

		switch (file_data[s]) {

			case 'v': { 
				vertices->push_back(
					parse_vertex(file_data , s , e)
				); 
			} break;

			case 'f': { 
				faces->push_back(
					parse_face(file_data, s, e)
				);
			} break;

			case 'n': { 
				vertices->push_back(
					parse_normal(file_data, s, e)
				); 
			} break;

			case 't': { 
				tvs->push_back(
					parse_texture_vertex(file_data, s, e)
				); 
			} break;

			default: break;
		}

	}

}

#endif
