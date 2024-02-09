
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
	graphics::frame_buffer = new buffer<scolor>(
		0, 0, window::width, window::height
	);

	if (graphics::frame_buffer == nullptr) {
		exceptions::show_error(
			"renderer error", "failed to allocate memory for 'frame buffer' !"
		);
		return false;
	}

	// setup bitmap

	ZeroMemory( &(graphics::bitmap) , sizeof(BITMAP) );

	graphics::bitmap.bmWidth  = window::width;
	graphics::bitmap.bmHeight = window::height;
	graphics::bitmap.bmPlanes = 1;
	graphics::bitmap.bmWidthBytes = sizeof(scolor);
	graphics::bitmap.bmBitsPixel  = sizeof(scolor)*8;
	graphics::bitmap.bmBits = frame_buffer->memory;
	graphics::bitmap.bmType = 0;

	// create a window compatible hdc for frame_buffer -> bitmap 
	graphics::bitmap_hdc = CreateCompatibleDC(window::hdc);

	// just a handle to the bitmap 
	graphics::hbitmap = CreateBitmap(
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

	// clear buffer
	ZeroMemory(
		frame_buffer->memory, frame_buffer->size * sizeof(scolor)
	);
	/*
	FillMemory(frame_buffer->memory, frame_buffer->size * sizeof(scolor), 0xfffff);
	*/


	GetClientRect(window::handle, &window::rect);
	/*
	ClientToScreen(window::handle, (LPPOINT)&window::rect.left);
	ClientToScreen(window::handle, (LPPOINT)&window::rect.top);
	*/

	// draw to buffer
	uint32_t Y = 0;
	for (uint16_t y = 0; y < 2; y += 1) {
		Y = y * frame_buffer->width;

		for (uint16_t x = 0; x < frame_buffer->width; x += 1) {
			frame_buffer->memory[Y+x] = color;
		}
	}

	// update bitmap buffer address
	SetBitmapBits(
		hbitmap,
		frame_buffer->size * sizeof(scolor),
		frame_buffer->memory
	);

	SelectObject(bitmap_hdc, hbitmap);

	// blt buffer into screen
	BitBlt(
		window::hdc,
		window::rect.left, window::rect.top,
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
