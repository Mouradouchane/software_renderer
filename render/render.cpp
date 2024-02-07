
#include "render.hpp"

#ifndef RENDER_CPP
#define RENDER_CPP


namespace graphics {

buffer<rgba8>* frame_buffer = nullptr;

bool init() {

	graphics::frame_buffer = new buffer<rgba8>(
		0, 0, window::width, window::height
	);

	if (graphics::frame_buffer == nullptr) {
		exceptions::show_error(
			"renderer error", "failed to allocate memory for 'frame buffer' !"
		);
		return false;
	}

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

	uint16_t r = std::rand() * 255 * 3;

	// clear buffer
	ZeroMemory(window::buffer, window::width * window::height);

	// draw to buffer
	for (size_t y = 0; y < window::height; y += 1) {
		for (size_t x = 0; x < window::width; x += 1) {
			window::buffer[y * window::width + x] = std::rand();
		}
	}

	// update bitmap buffer address
	SetBitmapBits(
		window::hbitmap, 
		sizeof(size_t) * window::width * window::height,
		window::buffer
	);

	SelectObject(window::bitmap_hdc, window::hbitmap);

	// blt buffer into screen
	BitBlt(
		window::hdc, 
		0, 0, 
		window::bitmap.bmWidth, 
		window::bitmap.bmHeight, 
		window::bitmap_hdc,
		0, 0,
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
