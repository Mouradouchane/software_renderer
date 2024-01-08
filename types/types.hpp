
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

typedef uint32_t     pixle[2];
typedef float32      sample[2];

// "typedef vectors" classe's wraper's
#ifndef VECTORS_HPP
	#include "vectors.hpp"
#endif

// "typedef colors" classe's wraper's
#ifndef COLORS_HPP
	#include "colors.hpp"
#endif

// 2D and 3D lines def's
#ifndef LINES_HPP
	#include "lines.hpp"
#endif

// 2D and 3D triangles def's
#ifndef TRIANGLES_HPP
	#include "triangles.hpp"
#endif

#endif
