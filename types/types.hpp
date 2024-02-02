
/*
	==============================
	all the types are defined here
	==============================
*/

#pragma once 

#ifndef _stdint
	#define _stdint	
	#include <stdint.h> // for int32 int64 ...
#endif

#ifndef TYPES_HPP
#define TYPES_HPP

/*
	=================================================
	================ standard types =================
	=================================================
*/

typedef float        float32 , *ptr_float32;
typedef double       float64 , *ptr_float64;
typedef long double  float96 , *ptr_float96;

#define FLOAT_TYPE 32

#if FLOAT_TYPE == 32
	#define sfloat float32
#else 
	#define sfloat float64
#endif

/*
	==========================================================
	======================== colors ==========================
	==========================================================
*/

typedef struct rgb8 {
	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue
};

typedef struct rgb16 {
	uint16_t r = 0; // red
	uint16_t g = 0; // green
	uint16_t b = 0; // blue
};

typedef struct rgb32 {
	uint32_t r = 0; // red
	uint32_t g = 0; // green
	uint32_t b = 0; // blue
};

typedef struct rgba8 {
	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue
	float32 a = 1.0f; // alpha 
};

typedef struct rgba16 {
	uint16_t r = 0; // red
	uint16_t g = 0; // green
	uint16_t b = 0; // blue
	float32  a = 1.0f; // alpha 
};

typedef struct rgba32 {
	uint32_t r = 0; // red
	uint32_t g = 0; // green
	uint32_t b = 0; // blue
	float32  a = 1.0f; // alpha 
};

rgb8  create_rgb8 (uint8_t  red, uint8_t  green, uint8_t  blue);
rgb16 create_rgb16(uint16_t red, uint16_t green, uint16_t blue);
rgb32 create_rgb32(uint32_t red, uint32_t green, uint32_t blue);

rgba8  create_rgba8 (uint8_t  red, uint8_t  green, uint8_t  blue, float32 alpha);
rgba16 create_rgba16(uint16_t red, uint16_t green, uint16_t blue, float32 alpha);


/*
	===================================================
	====================== vector's ===================
	===================================================
*/

typedef struct vec2d {
	sfloat x = 0;
	sfloat y = 0;
};

typedef struct vec3d {
	sfloat x = 0;
	sfloat y = 0;
	sfloat z = 1;
}; 

typedef struct vec4d {
	sfloat x = 0;
	sfloat y = 0;
	sfloat z = 1;
	sfloat w = 1;
};

vec2d create_vec2d(sfloat x=0, sfloat y=0);
vec3d create_vec3d(sfloat x=0, sfloat y=0, sfloat z=1);
vec4d create_vec4d(sfloat x=0, sfloat y=0, sfloat z=1, sfloat w=1);

/*
	=================================================
	=================== buffers =====================
	=================================================
*/

template<typename type> class buffer {

public : 
	
	uint16_t x = 0;
	uint16_t y = 0;

	uint16_t height = 1;
	uint16_t width  = 1;

	uint32_t size   = 0;
	type *   memory = nullptr; // heap allocation !

	// constructor's
	buffer(
		uint16_t x = 0, uint16_t y = 0,
		uint16_t width = 1, uint16_t height = 1
	);
	
	// destructor
	~buffer();

};


/*
	buffer template implementation
*/

template<typename type> buffer<type>::buffer(
	uint16_t x, uint16_t y,
	uint16_t width, uint16_t height
) {

	this->x = x;
	this->y = y;

	this->height = height;
	this->width  = width;

	this->size = width * height;

	this->memory = new type[this->size];

}

template<typename type> buffer<type>::~buffer() {

	if (this->memory != nullptr) {
		delete[] this->memory;
		this->memory = nullptr;
	}

}


typedef struct pixle {
	uint16_t x = 0;
	uint16_t y = 0;
	rgb8 color = { 0,0,0 };
};

template<typename type> struct sample {
	sfloat x = 0;
	sfloat y = 0;
	type value;
};


/*
	=================================================
	====================== lines ====================
	=================================================
*/

class line2d {

public:
	vec2d points[2];

	// constructor's
	line2d();
	line2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2  // point 2
	);
	line2d(vec2d const& point_1, vec2d const& point_2);

	// destructor
	~line2d() = default;

};
// end : class line2d 

class line3d {

public:
	vec3d points[2];

	// constructor's
	line3d();
	line3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2  // point 2
	);
	line3d(
		vec3d const& point_1, vec3d const& point_2
	);

	// destructor
	~line3d() = default;

};
// end : class line3d


/*
	===================================================
	====================== triangles ==================
	===================================================
*/

class triangle2d {

public:

	vec2d points[3];

	// constructor's
	triangle2d();

	triangle2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2, // point 2  
		sfloat x3, sfloat y3  // point 3
	);

	triangle2d(
		vec2d const& point_1,
		vec2d const& point_2,
		vec2d const& point_3
	);

	// destructor
	~triangle2d() = default;

};
// end : class triangle2d

class triangle3d {

public:

	vec3d points[3];

	// constructor's
	triangle3d();

	triangle3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2, // point 2
		sfloat x3, sfloat y3, sfloat z3  // point 3
	);

	triangle3d(
		vec3d const& point_1,
		vec3d const& point_2,
		vec3d const& point_3
	);

	// destructor
	~triangle3d() = default;

};
// end : class triangle3d


#endif
