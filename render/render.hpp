
/*
	in this file there is "render" function
	a function who responsible for call all 
	the rendering stage's .
*/

#include "../types/types.hpp"
#include "../math/math.hpp"
#include "../configs/configs.hpp"
#include "../window/window.hpp"
#include "../draw/draw.hpp"

#ifndef RENDER_HPP
#define RENDER_HPP

// our standard color system
#define scolor bgra8

namespace graphics{

	// main frame buffer we draw/raster in
	extern buffer<scolor>* frame_buffer;

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
