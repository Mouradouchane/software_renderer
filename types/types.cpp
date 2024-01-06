
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
	====================== VEC 2D ===================
	=================================================
*/

vec2d::vec2d() { }

vec2d::vec2d(float32 x, float32 y) : x{ x }, y{ y } 
{ 
}

/*
	=================================================
	====================== VEC 3D ===================
	=================================================
*/

vec3d::vec3d(){ }

vec3d::vec3d(float32 x, float32 y, float32 z)
	: x{ x }, y{ y }, z{ z } 
{
}

/*
	=================================================
	====================== VEC 4D ===================
	=================================================
*/

vec4d::vec4d() { }

vec4d::vec4d(float32 x, float32 y, float32 z , float32 w) 
	: x{ x }, y{ y }, z{ z } ,w{ w }
{
}

/*
	=================================================
	====================== RGBA 8 ===================
	=================================================
*/

rgba8::rgba8() { }

rgba8::rgba8(uint8_t red, uint8_t green, uint8_t blue)
	: r{red} , g{green} , b{blue}
{
}

rgba8::rgba8(uint8_t red, uint8_t green, uint8_t blue , float32 alpha)
	: r{ red }, g{ green }, b{ blue } , a{alpha}
{
}

/*
	=================================================
	====================== RGBA 16 ==================
	=================================================
*/

rgba16::rgba16() { }

rgba16::rgba16(uint16_t red, uint16_t green, uint16_t blue) 
	: r{ red }, g{ green }, b{ blue }
{
}

rgba16::rgba16(uint16_t red, uint16_t green, uint16_t blue, float32 alpha)
	: r{ red }, g{ green }, b{ blue }, a{ alpha }
{
}

#endif
