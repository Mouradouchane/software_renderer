
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

	// clear buffer
	window::d3d::device->Clear(0, 0, 0,0,0,0);

	// begin the scene
	window::d3d::device->BeginScene();
	
	// raster to buffer
	D3DCOLOR r = math::random::uint16() * math::random::uint16();
	window::d3d::device->ColorFill(window::d3d::surface , 0 , r);

	// end the scene
	window::d3d::device->EndScene();

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
