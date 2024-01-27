
/*
	==============================
	all the types are defined here
	==============================
*/

#ifndef _stdint
	#define _stdint	
	#include <stdint.h> // for int32 int64 ...
#endif

#ifndef TYPES_HPP

	#define TYPES_HPP

/*
	=================================================
	============ standard typedef's =================
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

// vector's based on array
typedef sfloat       vector2d[2];
typedef sfloat       vector3d[3];
typedef sfloat       vector4d[4];

typedef sfloat       matrix_2x2[2][2];
typedef sfloat       matrix_3x3[3][3];
typedef sfloat       matrix_4x4[4][4];

typedef uint8_t      srgb8[3];
typedef uint16_t     srgb16[3];
typedef uint32_t     srgb32[3];

typedef uint8_t      srgba8[4];
typedef uint16_t     srgba16[4];
typedef uint32_t     srgba32[4];

typedef struct pixle {
	uint32_t x = 0;
	uint32_t y = 0;
	srgba8 color = { 0,0,0,0 };
};

typedef struct sample {
	sfloat x = 0;
	sfloat y = 0;
	srgba8 color = { 0,0,0,0 };
};

// vector's based on struct
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
	==================== buffers ====================
	=================================================
*/

class pixels {

public : 
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t size   = 0;
	uint32_t height = 0;
	uint32_t width  = 0;

	pixle*   buffer = nullptr; // heap allocation !

	// constructor's
	pixels();
	pixels(uint32_t width , uint32_t height);
	
	// destructor
	~pixels();

	// todo 
	sample get_pixel(uint32_t x, uint32_t y);
	void   set_pixel(uint32_t x, uint32_t y, pixle new_value);

};

class samples {

public:
	uint32_t size   = 0;
	uint32_t height = 0;
	uint32_t width  = 0;
	sample*  buffer = nullptr; // heap allocation !

	// constructor's
	samples();
	samples(uint32_t width, uint32_t height);

	// destructor
	~samples();

	// todo 
	sample get_sample(uint32_t x, uint32_t y);
	void   set_sample(uint32_t x, uint32_t y, sample new_value);

};

/*
	=================================================
	==================== colors =====================
	=================================================
*/

// TODO : make rgba classes wrappers for srgba
class rgba8 { // 8bit rgba representation

public:

	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue

	float32 a = 1.0f; // alpha

	// constructor's
	rgba8();
	rgba8(uint8_t red, uint8_t green, uint8_t blue);
	rgba8(uint8_t red, uint8_t green, uint8_t blue, float32 alpha = 1.0f);

	// destructor
	~rgba8() = default;

	static const uint8_t MIN = 0;
	static const uint8_t MAX = UINT8_MAX;

};
// end : class rgb8

class rgba16 { // 16bit rgba representation

public:

	uint16_t r = 0; // red
	uint16_t g = 0; // green
	uint16_t b = 0; // blue

	float32 a = 1.0f; // alpha

	// constructor's
	rgba16();
	rgba16(uint16_t red, uint16_t green, uint16_t blue);
	rgba16(uint16_t red, uint16_t green, uint16_t blue, float32 alpha = 1.0f);

	// destructor
	~rgba16() = default;

	static const uint16_t MIN = 0;
	static const uint16_t MAX = UINT16_MAX;

};
// end : class rgb16


/*
	=================================================
	====================== lines ====================
	=================================================
*/
class line2d {

public:
	vector2d points[2];

	// constructor's
	line2d();
	line2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2  // point 2
	);
	line2d(vector2d  point_1, vector2d  point_2);
	line2d(vector2d& point_1, vector2d& point_2);

	// destructor
	~line2d() = default;

};
// end : class line2d 

class line3d {

public:
	vector3d points[2];

	// constructor's
	line3d();
	line3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2  // point 2
	);
	line3d(vector3d  point_1, vector3d  point_2);
	line3d(vector3d& point_1, vector3d& point_2);

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

	vector2d points[3];

	// constructor's
	triangle2d();

	triangle2d(
		sfloat x1, sfloat y1, // point 1
		sfloat x2, sfloat y2, // point 2  
		sfloat x3, sfloat y3  // point 3
	);

	triangle2d(
		vector2d point_1,
		vector2d point_2,
		vector2d point_3
	);

	triangle2d(
		vector2d& point_1,
		vector2d& point_2,
		vector2d& point_3
	);

	// destructor
	~triangle2d() = default;

};
// end : class triangle2d

class triangle3d {

public:

	vector3d points[3];

	// constructor's
	triangle3d();

	triangle3d(
		sfloat x1, sfloat y1, sfloat z1, // point 1
		sfloat x2, sfloat y2, sfloat z2, // point 2
		sfloat x3, sfloat y3, sfloat z3  // point 3
	);

	triangle3d(
		vector3d point_1,
		vector3d point_2,
		vector3d point_3
	);

	triangle3d(
		vector3d& point_1,
		vector3d& point_2,
		vector3d& point_3
	);

	// destructor
	~triangle3d() = default;

};
// end : class triangle3d


#endif
