
#include "render.hpp"

#ifndef RENDER_CPP
#define RENDER_CPP

namespace graphics {

buffer<scolor>* frame_buffer = nullptr;

BITMAPINFO bitmap_info = {0};
BITMAP  bitmap     = {0};
HBITMAP hbitmap    = NULL;
HDC     bitmap_hdc = NULL;

bool init() {

	// allocate buffer
	frame_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (frame_buffer == nullptr) {
		exceptions::show_error(
			"error", "failed to allocate memory for 'frame buffer' !"
		);
		return false;
	}

	GetClientRect(window::handle, &window::rect);
	AdjustWindowRectEx(&window::rect, window::style, 0, 0);

	ZeroMemory( &(bitmap) , sizeof(BITMAP) );

	// setup bitmap
	bitmap.bmWidth  = window::width;
	bitmap.bmHeight = window::height;
	bitmap.bmPlanes = 1;
	bitmap.bmWidthBytes = sizeof(scolor);
	bitmap.bmBitsPixel  = sizeof(scolor)*8;
	bitmap.bmBits = frame_buffer->memory;
	bitmap.bmType = 0;

	// create a window compatible hdc for frame_buffer -> bitmap 
	bitmap_hdc = CreateCompatibleDC(window::hdc);

	// just a handle to the bitmap 
	hbitmap = CreateBitmap(
		frame_buffer->width,
		frame_buffer->height,
		bitmap.bmPlanes,
		bitmap.bmBitsPixel,
		frame_buffer->memory
	);

	SelectObject(graphics::bitmap_hdc, graphics::hbitmap);

	return true;
}

void destroy() {
	
	if (graphics::frame_buffer != nullptr) {
		graphics::frame_buffer->~buffer();
		graphics::frame_buffer = nullptr;
	}

}

// todo : draw into frame_buffer
void draw() {

	scolor color = { 0 };
	color.a = 255;
	color.r = math::random::uint8();
	color.g = math::random::uint8();

	// clear buffer
	ZeroMemory(
		frame_buffer->memory, frame_buffer->size * sizeof(scolor)
	);

	// draw to buffer
	uint32_t Y = 0;
	for (uint16_t y = 0; y < frame_buffer->height; y += 1) {
		Y = y * frame_buffer->width;

		for (uint16_t x = 0; x < frame_buffer->width; x += 1) {
			frame_buffer->memory[Y+x] = color;
		}
	}

	// draw fps info  

	// update bitmap buffer address
	SetBitmapBits(
		hbitmap,
		frame_buffer->size * sizeof(scolor),
		frame_buffer->memory
	);

	SelectObject(bitmap_hdc, hbitmap);

	DrawTextA(
		bitmap_hdc,
		global::fps_msg.c_str(),
		global::fps_msg.length(),
		&(global::fps_msg_rect),
		DT_LEFT
	);

	// blt buffer into screen
	BitBlt(
		window::hdc,
		0,0,

		frame_buffer->width,
		frame_buffer->height,

		bitmap_hdc,
		0,0,
		SRCCOPY
	);

}

bool render() {
	
	// draw objects
	graphics::draw();

	return true;
}

}

#endif
