
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
	/*
	// window::lock_buffer();

	// clear buffer
	window::d3d::device->Clear(0,0,0,0,0,0);

	// begin the scene
	window::d3d::device->BeginScene();
	
	// raster to buffer
	D3DCOLOR r = math::random::uint16()* math::random::uint16();
	window::d3d::device->ColorFill(window::d3d::surface , 0 , r);

	// end the scene
	window::d3d::device->EndScene();

	// window::unlock_buffer();

	// displays buffer   
	window::d3d::device->Present(NULL, NULL, NULL, NULL);
	*/

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = window::width;
	bmi.bmiHeader.biHeight = window::height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	for (size_t y; y < 600; y += 1) {
		for (size_t x; x < 800;x += 1) {
			window::buffer[x * 800 + y] = math::random::uint16()*x*y;
		}
	}

	HDC hDesktopDC = GetDC(GetDesktopWindow());
	HBITMAP hDib = CreateDIBSection(hDesktopDC, &bmi, DIB_RGB_COLORS, (void**)&window::buffer, 0, 0);
	HDC hDibDC = CreateCompatibleDC(hDesktopDC);
	HGDIOBJ hOldObj = SelectObject(hDibDC, hDib);
	
	BitBlt(
		hDesktopDC,
		0,0,
		800,600,
		(HDC)window::buffer,
		0,0,
		SRCCOPY
	);
	ReleaseDC(GetDesktopWindow(), hDesktopDC);

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
