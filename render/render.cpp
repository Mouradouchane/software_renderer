
#include "render.hpp"

#ifndef RENDER_CPP
#define RENDER_CPP


namespace renderer {

buffer<rgba8>* frame_buffer = nullptr;

bool init() {

	renderer::frame_buffer = new buffer<rgba8>(
		0, 0, window::width, window::height
	);

	if (renderer::frame_buffer == nullptr) {
		exceptions::show_error("renderer error", "failed to allocate memory for 'frame buffer'");
		return false;
	}

	return true;
}

void destroy() {
	
	if (renderer::frame_buffer != nullptr) {
		delete renderer::frame_buffer;
		renderer::frame_buffer = nullptr;
	}

}

bool raster() {

	if (window::lock_buffer()) {
		// get pointer to the buffer 
		window::buffer = (uint32_t*)window::d3d::lock_rect_rslt.pBits;
	}
	else return false;

	// clear buffer
	ZeroMemory(window::buffer, window::size);

	// begin the scene
	window::d3d::device->BeginScene();
	BeginPaint(window::handle, 0);
	
	// copy frame_buffer to window buffer

	for (uint16_t y = 0; y < frame_buffer->height; y += 1) {
		for (uint16_t x = 0; x < frame_buffer->width; x += 1) {
			window::buffer[window::width * y + x] = math::random::uint16()*x*y;
		}
	}

	// end the scene
	EndPaint(window::handle, 0);
	window::d3d::device->EndScene();

	// unlook buffer
	window::unlock_buffer();

	// displays buffer   
	window::d3d::device->Present(NULL, NULL, NULL, NULL);

	return true;

}

bool render() {
	
	// if window buffer busy
	if (!renderer::raster()) {
		
	}

	return true;
}

}

#endif