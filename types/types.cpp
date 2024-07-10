
#pragma once 

#ifndef TYPES_CPP
#define TYPES_CPP

#include "types.hpp"

/*
	vector's creation
*/

vec2d create_vec2d(sfloat x, sfloat y){
	return { x , y };
}

vec3d create_vec3d(sfloat x, sfloat y, sfloat z){
	return { x , y , z };
}


/*
	colors creation
*/

rgb8 create_rgb8(uint8_t red, uint8_t green, uint8_t blue) {
	
	return { 
		red , green , blue 
	};
}

rgba8 create_rgba8(
	uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha
) {
	
	return { 
		red , green , blue , alpha 
	};
}

bgr8 create_bgr8(
	uint8_t red, uint8_t green, uint8_t blue
) {

	return bgr8 {
		blue, green, red,
	};
}

bgra8 create_bgra8(
	uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha
) {

	return bgra8 {
		blue, green, red, alpha
	};
}


// TODO : move those random function to random file in math folder
bgra8 random_bgra8(bool random_alpha) {

	if (random_alpha) {

		return bgra8{
			(uint8_t)(std::rand() % (256)) ,
			(uint8_t)(std::rand() % (256)) ,
			(uint8_t)(std::rand() % (256)) ,
			(uint8_t)(std::rand() % (256))
		
		
		};
	}
	else return bgra8{
		(uint8_t)(std::rand() % (256)) ,
		(uint8_t)(std::rand() % (256)) ,
		(uint8_t)(std::rand() % (256)) ,
		255
	};

}

// TODO : move those random function to random file in math folder
scolor random_scolor(bool random_alpha) {

	return scolor {
		(uint8_t)(std::rand() % (256)),
		(uint8_t)(std::rand() % (256)),
		(uint8_t)(std::rand() % (256)),
		(uint8_t)((random_alpha) ? (std::rand() % (256)) : 255)
	};
}


/*
	====================================
	=============== mesh ===============
	====================================
*/

mesh::mesh(
	std::vector<vec3d>& vertices
){
	v = vertices;
}

mesh::mesh(
	std::vector<vec3d>& vertices,
	std::vector<face3>& faces
){

	f = faces;
	v = vertices;
}

mesh::mesh(
	std::vector<vec3d>& vertices,
	std::vector<face3>& faces,
	std::vector<vec3d>& normals
){

	f  = faces;
	v  = vertices;
	n = normals;
}

mesh::mesh(
	std::vector<vec3d>& vertices,
	std::vector<face3>& faces,
	std::vector<vec3d>& normals,
	std::vector<vec_uv>& texture_coordinates
) {
	
	f  = faces;
	v  = vertices; 
	n  = normals;
	vt = texture_coordinates;
}

// destructor
mesh::~mesh() {

	this->v = std::vector<vec3d>();
	this->f = std::vector<face3>();
	this->n = std::vector<vec3d>();
	this->vt = std::vector<vec_uv>();

}

// static function
void mesh::move_mesh(mesh* source, mesh* destination) {
	std::memmove(destination, source, sizeof(mesh));
}

// static function
void mesh::copy_mesh(mesh* source, mesh* destination) {
	std::memcpy(destination, source, sizeof(mesh));
}


/*
	====================================
	============== faces ===============
	====================================
*/

face3::face3(
	indxs const& vertex_a, indxs const& vertex_b, indxs const& vertex_c
) :a{ vertex_a }, b{ vertex_b }, c{ vertex_c } 
{

}

indxs& face3::operator[](char vertex_name) {

	switch (vertex_name) {
		case 'a': return this->a;
		case 'b': return this->b;
		case 'c': return this->c;
	}

	return indxs{ 0 };
}

indxs& face3::operator[](uint8_t vertex_index) {

	switch (vertex_index) {
		case 0 : return this->a;
		case 1 : return this->b;
		case 2 : return this->c;
	}

	return indxs{ 0 };
}

// ===== face4 =========================================

face4::face4(
	indxs const& vertex_a, indxs const& vertex_b, 
	indxs const& vertex_c, indxs const& vertex_d
) 
  : face3(vertex_a, vertex_b, vertex_c), d{ vertex_d }
{

}

indxs& face4::operator[](char vertex_name) {

	switch (vertex_name) {
		case 'a': return this->a;
		case 'b': return this->b;
		case 'c': return this->c;
		case 'd': return this->d;
	}

	return indxs{ 0 };
}

indxs& face4::operator[](uint8_t vertex_index) {

	switch (vertex_index) {
		case 0: return this->a;
		case 1: return this->b;
		case 2: return this->c;
		case 3: return this->d;
	}

	return indxs{ 0 };
}

#endif
