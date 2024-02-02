
/*
	here all the rasterization function for 2d & 3d 
	shapes , lines and triangles :)
*/

#include "../window/window.hpp"
#include "../types/types.hpp"
#include "../math/math.hpp"

#ifndef DRAW_HPP
#define DRAW_HPP

namespace draw {

	// buffer for draw/rasterization
	extern buffer<rgb8> * frame_buffer;

	bool init(buffer<rgb8>* frame_buffer_);
	bool destroy();

	void line(line2d& line);
	void line(line3d& line);

	void triangle(triangle2d& triangle);
	void triangle(triangle3d& triangle);

/*  TODO : implement curves
	void curve(curve2d& curve);
	void curve(curve3d& curve);
*/
	
	void set_pixle(uint16_t x, uint16_t y, rgb8& color);

	void set_pixle_with_blend(
		uint16_t x, uint16_t y, rgba8& color
	);
	
	void set_sample(sfloat x, sfloat y, rgba8& color);

	// alpha blending 
	void blend_pxiels(rgba8& back_color, rgba8& front_color);

}
// end : namespace draw

#endif