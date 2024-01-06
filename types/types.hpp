
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


typedef float        float32 , *ptr_float32;
typedef double       float64 , *ptr_float64;
typedef long double  float96 , *ptr_float96;

typedef float32      vector2d[2];
typedef float32      vector3d[3];
typedef float32      vector4d[4];

typedef uint8_t      srgb8[3];
typedef uint16_t     srgb16[3];
typedef uint32_t     srgb32[3];

class vec2d {

public :

	float32 x = 0;
	float32 y = 0;
	// constructor's
	vec2d();
	vec2d(float32 x , float32 y);

	// destructor
	~vec2d() = default;

};

// end : vector 2D 


class vec3d {

public :

	float32 x = 0;
	float32 y = 0;
	float32 z = 1.0f;

	// constructor's
	vec3d();
	vec3d(float32 x , float32 y , float32 z = 1.0f);

	// destructor
	~vec3d() = default;

};
// end of vec3d class


class vec4d {

public : 

	float32 x = 0;
	float32 y = 0;
	float32 z = 1.0f;
	float32 w = 1.0f;
	
	// constructor's
	vec4d();
	vec4d(float32 x , float32 y , float32 z = 1.0f , float32 w = 1.0f);

	// destructor
	~vec4d() = default;

};
// end of vec4d class


class rgba8 { // 8bit rgba representation

public :

	uint8_t r = 0; // red
	uint8_t g = 0; // green
	uint8_t b = 0; // blue

	float32 a = 1.0f; // alpha

	// constructor's
	rgba8();
	rgba8(uint8_t red , uint8_t green , uint8_t blue);
	rgba8(uint8_t red , uint8_t green , uint8_t blue , float32 alpha = 1.0f);

	// destructor
	~rgba8() = default;

	static const uint8_t MIN = 0;
	static const uint8_t MAX = UINT8_MAX;

};
// end of rgb8 class


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
	~rgba16();

	static const uint16_t MIN = 0;
	static const uint16_t MAX = UINT16_MAX;

};

#endif
