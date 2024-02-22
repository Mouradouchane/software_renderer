

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"
// #include "draw.cpp"

namespace graphics {

buffer<scolor>* front_buffer = nullptr;
buffer<scolor>* back_buffer  = nullptr;

BITMAPINFO bitmap_info = { 0 };
BITMAP     bitmap = { 0 };
HBITMAP    hbitmap = NULL;
HDC        bitmap_hdc = NULL;

scolor clear_color = { 0,0,0,0 };

bool init() {

	clear_color.a = 255;

	// allocate back-buffer
	back_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (back_buffer == nullptr) {
		exceptions::show_error(
			global::error_title, "failed to allocate memory for 'back buffer' !"
		);
		return false;
	}

	// allocate front-buffer
	front_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (front_buffer == nullptr) {
		exceptions::show_error(
			global::error_title, "failed to allocate memory for 'front buffer' !"
		);
		return false;
	}

	GetClientRect(window::handle, &window::rect);
	AdjustWindowRectEx(&window::rect, window::style, 0, 0);

	ZeroMemory(&(bitmap), sizeof(BITMAP));

	// setup bitmap
	bitmap.bmWidth  = window::width;
	bitmap.bmHeight = window::height;
	bitmap.bmPlanes = 1;
	bitmap.bmWidthBytes = sizeof(scolor);
	bitmap.bmBitsPixel  = sizeof(scolor) * 8;
	bitmap.bmBits = back_buffer->memory;
	bitmap.bmType = 0;

	// create a window compatible hdc for frame_buffer -> bitmap 
	bitmap_hdc = CreateCompatibleDC(window::hdc);

	// just a handle to the bitmap 
	hbitmap = CreateBitmap(
		back_buffer->width,
		back_buffer->height,
		bitmap.bmPlanes,
		bitmap.bmBitsPixel,
		back_buffer->memory
	);

	SelectObject(graphics::bitmap_hdc, graphics::hbitmap);

	return true;
}

void destroy() {

	if (graphics::front_buffer != nullptr) {
		graphics::front_buffer->~buffer();
		graphics::front_buffer = nullptr;
	}

	if (graphics::back_buffer != nullptr) {
		graphics::back_buffer->~buffer();
		graphics::back_buffer  = nullptr;
	}

}

void draw_fps_info() {

	global::fps_msg = "FPS : " + std::to_string(preformance::fps);

	DrawTextA(
		bitmap_hdc,
		global::fps_msg.c_str(),
		global::fps_msg.length(),
		&(global::fps_msg_rect),
		DT_LEFT
	);

	global::loop_msg = "LOOP TIME : " + std::to_string(preformance::total_taken_time) + "ms";

	DrawTextA(
		bitmap_hdc,
		global::loop_msg.c_str(),
		global::loop_msg.length(),
		&(global::loop_msg_rect),
		DT_LEFT
	);

}

void rasterization() {

	// clear buffer
	back_buffer->fill(clear_color);

	// draw to buffer
	/*
	draw::line(vec2d{ 10,10 }, vec2d{ 10,300 }, scolor{ 0,0,255,255 });
	draw::line(vec2d{ 10,10 }, vec2d{ 25,300 }, scolor{0,120,255,255});
	draw::line(vec2d{ 250,650 }, vec2d{ 1000,300 }, scolor{ 255,0,0,255 });
	draw::line(vec2d{ 1100,320 }, vec2d{ 250,150 }, scolor{ 255,111,0,255 });
	draw::line(vec2d{ 10,10 }, vec2d{ 300,10 }, scolor{ 0,255,0,255 });
	draw::line(vec2d{ 10,10 }, vec2d{ 300,25 }, scolor{ 255,255,0,255 });
	
	draw::draw_triangle(
		vec2d{ 100,100 }, vec2d{ 200,100 }, vec2d{ 200,200 },
		scolor{ 0,255,0,255 }
	);
	*/

	draw::fill_triangle(
		vec2d{ 100,100 }, vec2d{ 200,100 }, vec2d{ 200,200 },
		scolor{ 255,0,0,100 }
	);
	draw::fill_triangle(
		vec2d{ 600,100 }, vec2d{ 200,100 }, vec2d{ 200,200 },
		scolor{ 0,0,255,100 }
	);
	draw::fill_triangle(
		vec2d{ 600,100 }, vec2d{ 200,200 }, vec2d{ 600,400 },
		scolor{ 0,255,0,100 }
	);
	draw::fill_triangle(
		vec2d{ 230,470 }, vec2d{ 200,200 }, vec2d{ 600,400 },
		scolor{ 255,255,0,100 }
	);
	draw::fill_triangle(
		vec2d{ 230,470 }, vec2d{ 200,200 }, vec2d{ 100,100},
		scolor{ 120,80,200,100 }
	);

	// update bitmap buffer address
	SetBitmapBits(
		hbitmap,
		back_buffer->size * sizeof(scolor),
		back_buffer->memory
	);

	SelectObject(bitmap_hdc, hbitmap);
	 
	if(config::draw_fps_info) draw_fps_info();

	// blt buffer into screen
	BitBlt(
		window::hdc,
		0,0,

		back_buffer->width,
		back_buffer->height,

		bitmap_hdc,
		0,0,
		SRCCOPY
	);

	// swap buffers
	std::swap(front_buffer, back_buffer);
}

bool render() {
	
	// draw objects
	graphics::rasterization();

	return true;
}

}

#endif
