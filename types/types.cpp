
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

vec2d::vec2d() { }

vec2d::vec2d(sfloat x, sfloat y) {

	this->vector[0] = x;
	this->vector[1] = y;

}

vec3d::vec3d() { }

vec3d::vec3d(sfloat x, sfloat y, sfloat z) {

	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;

}

vec4d::vec4d() { }

vec4d::vec4d(sfloat x, sfloat y, sfloat z, sfloat w) {

	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	this->vector[3] = w;

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

	this->points[0][0] = x1;
	this->points[0][1] = y1;

	this->points[1][0] = x2;
	this->points[1][1] = y2;

}

line2d::line2d(vector2d point_1, vector2d point_2) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];

}

line2d::line2d(vector2d& point_1, vector2d& point_2) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];

}

line3d::line3d() { }

line3d::line3d(
	sfloat x1, sfloat y1, sfloat z1, // point 1
	sfloat x2, sfloat y2, sfloat z2  // point 2
) {

	this->points[0][0] = x1;
	this->points[0][1] = y1;
	this->points[0][2] = z1;

	this->points[1][0] = x2;
	this->points[1][1] = y2;
	this->points[1][2] = z2;

}

line3d::line3d(vector3d point_1, vector3d point_2) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];
	this->points[0][2] = point_1[2];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];
	this->points[1][2] = point_2[2];

}

line3d::line3d(vector3d& point_1, vector3d& point_2) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];
	this->points[0][2] = point_1[2];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];
	this->points[1][2] = point_2[2];

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

	this->points[0][0] = x1;
	this->points[0][1] = y1;

	this->points[1][0] = x2;
	this->points[1][1] = y2;

	this->points[2][0] = x3;
	this->points[2][1] = y3;

}

triangle2d::triangle2d(
	vector2d point_1, vector2d point_2, vector2d point_3
) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];

	this->points[2][0] = point_3[0];
	this->points[2][1] = point_3[1];

}


triangle2d::triangle2d(
	vector2d& point_1, vector2d& point_2, vector2d& point_3
) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];

	this->points[2][0] = point_3[0];
	this->points[2][1] = point_3[1];

}

triangle3d::triangle3d() { }

triangle3d::triangle3d(
	sfloat x1, sfloat y1, sfloat z1, // point 1
	sfloat x2, sfloat y2, sfloat z2, // point 2
	sfloat x3, sfloat y3, sfloat z3  // point 3
) {

	this->points[0][0] = x1;
	this->points[0][1] = y1;
	this->points[0][2] = z1;

	this->points[1][0] = x2;
	this->points[1][1] = y2;
	this->points[1][2] = z2;

	this->points[2][0] = x3;
	this->points[2][1] = y3;
	this->points[2][2] = z3;

}

triangle3d::triangle3d(
	vector3d point_1, vector3d point_2, vector3d point_3
) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];
	this->points[0][2] = point_1[2];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];
	this->points[1][2] = point_2[2];

	this->points[2][0] = point_3[0];
	this->points[2][1] = point_3[1];
	this->points[2][2] = point_3[2];

}

triangle3d::triangle3d(
	vector3d& point_1, vector3d& point_2, vector3d& point_3
) {

	this->points[0][0] = point_1[0];
	this->points[0][1] = point_1[1];
	this->points[0][2] = point_1[2];

	this->points[1][0] = point_2[0];
	this->points[1][1] = point_2[1];
	this->points[1][2] = point_2[2];

	this->points[2][0] = point_3[0];
	this->points[2][1] = point_3[1];
	this->points[2][2] = point_3[2];

}


/*
	===================================================
	====================== buffers ====================
	===================================================
*/

pixels::pixels() { }

pixels::pixels(uint32_t width, uint32_t height) {

	this->height = height;
	this->width  = width;
	this->size   = width * height;

	this->buffer = new pixle[this->size * sizeof(pixle)];

}

pixels::~pixels() {

	if (this->buffer != nullptr) {
		delete[] this->buffer;
		this->buffer = nullptr;
	}

}

samples::samples() { }

samples::samples(uint32_t width, uint32_t height) {

	this->height = height;
	this->width  = width;
	this->size   = width * height;

	this->buffer = new sample[this->size * sizeof(sample)];

}

samples::~samples() {

	if (this->buffer != nullptr) {
		delete[] this->buffer;
		this->buffer = nullptr;
	}

}

#endif
