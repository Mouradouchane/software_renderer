
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
	HINSTANCE hinst, window_proc proc , int n_cmd_show ,
	std::string const& name, 
	size_t width, size_t height
){

	// window props setup

	this->name = name.c_str();
	this->width = width;
	this->height = height;

	this->proc = proc;
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

void window::set_proc( window_proc win_proc ) {

	this->proc = win_proc;

}

bool window::is_window_created() {
	return (this->hwnd != NULL);
}

bool window::show() {

	if (this->hwnd == NULL && !(this->visible) ) return false;
	
	else return ShowWindow(this->hwnd , this->n_cmd_show);
	
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
}

void window::set_height(size_t new_height) {
	this->height = new_height;
}

void window::set_width(size_t new_width){
	this->width = new_width;
}

void window::set_x(size_t new_x){
	this->x = new_x;
}

void window::set_y(size_t new_y){
	this->y = new_y;
}

#endif

