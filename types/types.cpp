
#include "types.hpp"

#ifndef TYPES_CPP
#define TYPES_CPP

/*
	few function for vector's creation
*/

vec2d create_vec2d(sfloat x, sfloat y){
	vec2d  vector = { x , y };
	return vector;
}

vec3d create_vec3d(sfloat x, sfloat y, sfloat z) {
	vec3d  vector = { x = x , y = y , z = z };
	return vector;
}

vec4d create_vec4d(sfloat x, sfloat y, sfloat z , sfloat w) {
	vec4d  vector = { x = x , y = y , z = z , w = w};
	return vector;
}

/*
	few functions for colors creation
*/

rgb8 create_rgb8(uint8_t red, uint8_t green, uint8_t blue) {
	return { red , green , blue };
}

rgb16 create_rgb16(uint16_t red, uint16_t green, uint16_t blue) {
	return { red , green , blue };
}

rgb32 create_rgb32(uint32_t red, uint32_t green, uint32_t blue) {
	return { red , green , blue };
}

rgba8 create_rgba8(
	uint8_t  red, uint8_t  green, uint8_t  blue, uint8_t alpha
) {
	return { red , green , blue , alpha };
}
rgba16 create_rgba16(
	uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha
){
	return { red , green , blue , alpha };
}

rgba32 create_rgba32(
	uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha
){
	return { red , green , blue , alpha };
}

/*
	=================================================
	====================== lines ====================
	=================================================
*/

line2d::line2d() { }

line2d::line2d(
	sfloat x1, sfloat y1, sfloat x2, sfloat y2
) {

	this->points[0].x = x1;
	this->points[0].y = y1;

	this->points[1].x = x2;
	this->points[1].y = y2;

}

line2d::line2d(vec2d const& point_1, vec2d const& point_2) {

	this->points[0] = point_1;
	this->points[1] = point_2;

}

line3d::line3d() { }

line3d::line3d(
	sfloat x1, sfloat y1, sfloat z1, // point 1
	sfloat x2, sfloat y2, sfloat z2  // point 2
) {

	this->points[0].x = x1;
	this->points[0].y = y1;
	this->points[0].z = z1;

	this->points[1].x = x2;
	this->points[1].y = y2;
	this->points[1].z = z2;

}

line3d::line3d(
	vec3d const& point_1, vec3d const& point_2
) {

	this->points[0] = point_1;
	this->points[1] = point_2;

}

/*
	===================================================
	====================== triangles ==================
	===================================================
*/

triangle2d::triangle2d() { }

triangle2d::triangle2d(
	sfloat x1, sfloat y1, // point 1
	sfloat x2, sfloat y2, // point 2  
	sfloat x3, sfloat y3  // point 3
) {

	this->points[0].x = x1;
	this->points[0].y = y1;

	this->points[1].x = x2;
	this->points[1].y = y2;

	this->points[2].x = x3;
	this->points[2].y = y3;

}

triangle2d::triangle2d(
	vec2d const& point_1 , vec2d const& point_2 , vec2d const& point_3
){

	this->points[0] = point_1;
	this->points[1] = point_2;
	this->points[2] = point_3;

}


triangle3d::triangle3d() { }

triangle3d::triangle3d(
	sfloat x1, sfloat y1, sfloat z1, // point 1
	sfloat x2, sfloat y2, sfloat z2, // point 2
	sfloat x3, sfloat y3, sfloat z3  // point 3
) {

	this->points[0].x = x1;
	this->points[0].y = y1;
	this->points[0].z = z1;

	this->points[1].x = x2;
	this->points[1].y = y2;
	this->points[1].z = z2;

	this->points[2].x = x3;
	this->points[2].y = y3;
	this->points[2].z = z3;

}

triangle3d::triangle3d(
	vec3d const& point_1,
	vec3d const& point_2,
	vec3d const& point_3
) {

	this->points[0] = point_1;
	this->points[1] = point_2;
	this->points[2] = point_3;

}

#endif
