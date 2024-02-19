

#ifndef RENDER_CPP
#define RENDER_CPP

#include "render.hpp"

namespace graphics {

buffer<scolor>* front_buffer = nullptr;
buffer<scolor>* back_buffer = nullptr;

BITMAPINFO bitmap_info = { 0 };
BITMAP  bitmap = { 0 };
HBITMAP hbitmap = NULL;
HDC     bitmap_hdc = NULL;

bool init() {

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

	global::loop_msg = "LOOP TIME : " + std::to_string(preformance::total_taken_time);

	DrawTextA(
		bitmap_hdc,
		global::loop_msg.c_str(),
		global::loop_msg.length(),
		&(global::loop_msg_rect),
		DT_LEFT
	);

}

bool inc = true;
scolor color = { 0,0,100,255 };

std::thread rt(
	[&]() {

		while (global::running) {
			if (color.r >= 254) inc = false;
			if (color.r == 0) inc = true;
			color.r += ((inc) ? 1 : -1);
			color.b += ((inc) ? 1 : -1);

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		
	}
);

void draw() {

	// clear buffer
	ZeroMemory(
		back_buffer->memory, back_buffer->size * sizeof(scolor)
	);

	// draw to buffer
	uint32_t Y = 0;
	for (uint16_t y = 0; y < back_buffer->height; y += 1) {
		Y = y * back_buffer->width;
		for (uint16_t x = 0; x < back_buffer->width; x += 1) {
			back_buffer->memory[Y+x] = color;
		}
	}

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
	//std::swap(front_buffer, back_buffer);
}

bool render() {
	
	// draw objects
	graphics::draw();

	return true;
}

}

#endif
