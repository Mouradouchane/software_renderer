
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

typedef uint8_t      rgb8[3];
typedef uint16_t     rgb16[3];
typedef uint32_t     rgb32[3];

typedef uint8_t      rgba8[4];
typedef uint16_t     rgba16[4];
typedef uint32_t     rgba32[4];

// define standard type of rgb/rgba 
// to be the main coloring system
#define STANDARD_RGB 8

#if STANDARD_RGB == 8

	typedef rgb8  srgb;
	typedef rgba8 srgba;

#elif STANDARD_RGB == 16

	typedef rgb16  srgb;
	typedef rgba16 srgba;

#else
	typedef rgb32  srgb;
	typedef rgba32 srgba;
#endif

typedef struct pixle {
	uint16_t x = 0;
	uint16_t y = 0;
	srgb color;
};

template<typename type> struct sample {
	sfloat x = 0;
	sfloat y = 0;
	type value;
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
	=============== template buffer =================
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
	buffer(uint16_t width=1 , uint16_t height=1);
	buffer(
		uint16_t x = 0, uint16_t y = 0,
		uint16_t width = 1, uint16_t height = 1
	);
	
	// destructor
	~buffer();

};

/*
	=================================================
	==================== colors =====================
	=================================================
*/

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
