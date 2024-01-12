
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
	HINSTANCE hinst, WNDPROC proc_function , int n_cmd_show ,
	std::string const& name, 
	size_t width, size_t height
){

	// window props setup

	this->name   = name.c_str();
	this->width  = width;
	this->height = height;

	this->frame_buffer = pixels(width, height);

	this->hinst = hinst;
	this->n_cmd_show = n_cmd_show;

	this->wc.hInstance = this->hinst;

	this->ptr_proc = proc_function;
	this->wc.lpfnWndProc = this->ptr_proc;

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

/*
void window::set_proc( WNDPROC win_proc ) {
	this->ptr_proc = win_proc;
}
*/

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

	this->bitmap_info.bmiHeader.biSize = sizeof(
		this->bitmap_info.bmiHeader
	);
	this->bitmap_info.bmiHeader.biPlanes = 1;
	this->bitmap_info.bmiHeader.biBitCount = 32;
	this->bitmap_info.bmiHeader.biCompression = BI_RGB;
	window_hdc = CreateCompatibleDC(0);
	
	this->h_bitmap = CreateDIBSection(
		this->window_hdc ,
		&(this->bitmap_info) ,
		DIB_RGB_COLORS ,
		(void**)this->frame_buffer.buffer ,
		NULL , 0 
	);

}

// force to send mw_paint message for 
void window::send_update_message() {

	InvalidateRect(this->hwnd, NULL, FALSE);
	UpdateWindow(this->hwnd);

}

void window::on_paint() {

	RECT rect; int width = 0, height = 0;

	if (GetWindowRect(this->hwnd, &rect)) {
		width  = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	HDC dest_hdc;

	dest_hdc = BeginPaint(this->hwnd, &(this->paint_struct));
	
	BitBlt(
		dest_hdc,
		0, 0, // x , y
		this->frame_buffer.width , 
		this->frame_buffer.height, // w , h
		this->window_hdc, // source hdc
		0,0,
		SRCCOPY // copy bitmap to window buffer
	);

	EndPaint(this->hwnd, &(this->paint_struct));

}

void window::on_resize(LPARAM lp) {

	RECT rect; int width = 0, height = 0;

	if (GetWindowRect(this->hwnd, &rect)) {
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	FillRect(
		this->window_hdc,
		&rect ,
		(HBRUSH)(100)
	);

}

#endif

