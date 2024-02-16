
/*
	in this file there is "render" function
	a function who responsible for call all 
	the rendering stage's .
*/

#ifndef RENDER_HPP
#define RENDER_HPP

#include "../types/types.hpp"
#include "../math/math.hpp"
#include "../preformance/preformance.hpp"
#include "../configs/configs.hpp"
#include "../window/window.hpp"
#include "../draw/draw.hpp"

namespace graphics{

	// main frame buffer's
	extern buffer<scolor>* back_buffer;
	extern buffer<scolor>* front_buffer;

	// bitmap & hdc for gdi
	extern BITMAP  bitmap;
	extern HBITMAP hbitmap;
	extern HDC     bitmap_hdc;
	extern BITMAPINFO bitmap_info;

	bool init();
	void destroy();

	// raster generate buffer to screen buffer
	void draw();

	bool render();

}
// end : graphics namespace

#endif
