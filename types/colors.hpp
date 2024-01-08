
/*
	=================================================
	====================== colors ===================
	=================================================
*/

#ifndef _stdint
	#define _stdint	
	#include <stdint.h> // for int32 int64 ...
#endif

#ifndef COLORS_HPP 

    #define COLORS_HPP 

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
	~rgba16();

	static const uint16_t MIN = 0;
	static const uint16_t MAX = UINT16_MAX;

};
// end : class rgb16

#endif
