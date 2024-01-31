
#ifndef _stdint
	#define _stdint	
	#include <stdint.h>
#endif

#ifndef TYPES_HPP
	#include "types.hpp"
#endif

#ifndef TYPES_CPP

#define TYPES_CPP

/*
	=================================================
	===================== vectors ===================
	=================================================
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
	=================================================
	==================== colors =====================
	=================================================
*/

rgba8::rgba8() { }

rgba8::rgba8(uint8_t red, uint8_t green, uint8_t blue)
	: r{ red }, g{ green }, b{ blue }
{
}

rgba8::rgba8(uint8_t red, uint8_t green, uint8_t blue, float32 alpha)
	: r{ red }, g{ green }, b{ blue }, a{ alpha }
{
}


rgba16::rgba16() { }

rgba16::rgba16(uint16_t red, uint16_t green, uint16_t blue)
	: r{ red }, g{ green }, b{ blue }
{
}

rgba16::rgba16(uint16_t red, uint16_t green, uint16_t blue, float32 alpha)
	: r{ red }, g{ green }, b{ blue }, a{ alpha }
{
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


/*
	===================================================
	================ template buffer ==================
	===================================================
*/

template<typename type> buffer<type>::buffer(
	uint16_t width, uint16_t height
){

	this->height = height;
	this->width  = width;

	this->size   = width * height;

	this->memory = new type[ this->size ];

}

template<typename type> buffer<type>::buffer(
	uint16_t x , uint16_t y ,
	uint16_t width , uint16_t height
) {

	this->x = x;
	this->y = y;

	this->height = height;
	this->width = width;

	this->size = width * height;

	this->memory = new type[this->size];

}

template<typename type> buffer<type>::~buffer() {

	if (this->memory != nullptr) {
		delete[] this->memory;
		this->memory = nullptr;
	}

}


#endif
