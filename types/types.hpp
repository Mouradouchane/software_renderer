
/*
	==============================
	all the types are defined here
	==============================
*/

#ifndef _stdint
	#define _stdint	
	#include <stdint.h>
#endif

#ifdef X64
	typedef int64_t sint, *sint;
	typedef float sfloat, *sfloat;
#else
	typedef int32_t sint, * sint;
	typedef uint32_t suint , *suint;

	typedef float sfloat, * sfloat;
	typedef ufloat sufloat , *sufloat;
#endif

class vec2d {

};

class vec3d {

};

class vec4d {

};

class rgba {

};

