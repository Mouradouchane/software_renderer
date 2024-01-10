
#ifndef WINDOW_H
	#define WINDOW_H
	#include <windows.h>
#endif

#ifndef STD_STRING
	#define STD_STRING
	#include <string>
#endif

#ifndef WINDOW_CLASS_HPP
	#include "window.hpp"
#endif

#ifndef WINDOW_CLASS_CPP

	#define WINDOW_CLASS_CPP

/*
   ========== constructor ========== 
*/

window::window(
	HINSTANCE hinst, int n_cmd_show ,
	std::string const& name, 
	size_t width, size_t height
){

	// window props setup

	this->name = name.c_str();
	this->width = width;
	this->height = height;

	this->hinst = hinst;
	this->n_cmd_show = n_cmd_show;

	this->wc.hInstance = this->hinst;

	this->wc.lpfnWndProc = this->proc;

	std::wstring stemp = std::wstring(this->name.begin(), this->name.end());
	this->wc.lpszClassName = stemp.c_str();

	// window registeration

	RegisterClassW(&wc);

	// window creation

	this->hwnd = CreateWindowW(
		this->wc.lpszClassName,
		this->wc.lpszClassName,

		this->style , this->x , this->y , 
		this->width , this->height ,

		NULL , NULL , this->hinst , NULL   
	);

	this->visible = (ShowWindow(this->hwnd, this->n_cmd_show) == 0);

	// setup handel devince context
	this->setup_bitmap_context();

}

/*
   ========== destructor ==========
*/
window::~window() {

	// TODO : !!!

}

/*

   ========== method's ==========

*/

void window::set_proc( WNDPROC win_proc ) {

	this->ptr_proc = win_proc;

}

bool window::is_window_created() {
	return (this->hwnd != NULL);
}

bool window::show() {

	if (this->hwnd == NULL && !(this->visible) ) return false;
	
	else return ShowWindow(this->hwnd , this->n_cmd_show);
	
}

bool window::hide() {

	if (this->hwnd == NULL && !(this->visible)) return false;

	else return ShowWindow(this->hwnd , SW_HIDE);

}

bool window::destroy() {

	if (this->hwnd == NULL) return false;
	else {
		return DestroyWindow(this->hwnd);
	}
}

std::string window::get_name() {
	return this->name;
}

size_t window::get_height() {
	return this->height;
}

size_t window::get_width() {
	return this->width;
}

size_t window::get_x() {
	return this->x;
}

size_t window::get_y() {
	return this->y;
}

void window::set_name(std::string const& new_name) {
	
	this->name = new_name;

	if (this->hwnd != NULL) {
		SetWindowTextW(this->hwnd, (const wchar_t*)this->name.c_str());
	}

}

void window::set_height(size_t new_height) {
	this->height = new_height;

	if (this->hwnd != NULL) {

		SetWindowPos(
			this->hwnd, 0, this->x, this->y,
			this->width, this->height, SWP_DEFERERASE
		);

	}

}

void window::set_width(size_t new_width){
	this->width = new_width;

	if (this->hwnd != NULL) {

		SetWindowPos(
			this->hwnd, 0, this->x, this->y,
			this->width, this->height, SWP_DEFERERASE
		);

	}

}

void window::set_x(size_t new_x){
	this->x = new_x;

	if (this->hwnd != NULL) {

		SetWindowPos(
			this->hwnd, 0, this->x, this->y , 
			this->width , this->height , SWP_DEFERERASE
		);

	}

}

void window::set_y(size_t new_y){
	this->y = new_y;

	if (this->hwnd != NULL) {

		SetWindowPos(
			this->hwnd, 0, this->x, this->y,
			this->width, this->height, SWP_DEFERERASE
		);

	}

}

void window::setup_bitmap_context() {

	frame_bitmap_info.bmiHeader.biSize = sizeof(frame_bitmap_info.bmiHeader);
	frame_bitmap_info.bmiHeader.biPlanes = 1;
	frame_bitmap_info.bmiHeader.biBitCount = 32;
	frame_bitmap_info.bmiHeader.biCompression = BI_RGB;
	frame_device_context = CreateCompatibleDC(0);
	
}

// force to send mw_paint message for 
void window::send_update_message() {

	InvalidateRect(this->hwnd, NULL, FALSE);
	UpdateWindow(this->hwnd);

}

void window::on_paint() {

	HDC device_context;

	device_context = BeginPaint(this->hwnd, &(this->paint_struct));
	BitBlt(
		device_context,
		this->paint_struct.rcPaint.left, 
		this->paint_struct.rcPaint.top,
		this->paint_struct.rcPaint.right  - this->paint_struct.rcPaint.left,
		this->paint_struct.rcPaint.bottom - this->paint_struct.rcPaint.top,
		this->frame_device_context,
		this->paint_struct.rcPaint.left, 
		this->paint_struct.rcPaint.top,
		SRCCOPY // copy bitmap to window buffer
	);

	EndPaint(this->hwnd, &(this->paint_struct));

}

void window::on_resize() {
	/*
	frame_bitmap_info.bmiHeader.biWidth = LOWORD(lParam);
	frame_bitmap_info.bmiHeader.biHeight = HIWORD(lParam);

	if (frame_bitmap) DeleteObject(frame_bitmap);
	frame_bitmap = CreateDIBSection(NULL, &frame_bitmap_info, DIB_RGB_COLORS, (void**)&frame.pixels, 0, 0);
	SelectObject(frame_device_context, frame_bitmap);

	frame.width = LOWORD(lParam);
	frame.height = HIWORD(lParam);
	*/

}

LRESULT CALLBACK window::proc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {

	switch (uMsg) {

	case WM_DESTROY: {

		PostQuitMessage(0);
		ExitProcess(0);
		return 0;

	}

	case WM_PAINT: {
		/*
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		*/

		this->on_paint();

		return 0;
	}

	case WM_SIZE: {

		return 0;
	}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

#endif

