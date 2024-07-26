
/*
	=================================================
	program window and it's props here in 'namespace' 
	=================================================
*/

#pragma once 

#ifndef WINDOW_HPP
#define WINDOW_HPP

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wingdi.h>
#include <string>

#include "global.hpp"
#include "types.hpp"
//#include "configs.hpp"
//#include "math.hpp"
//#include "render.hpp"

namespace window {

	extern const wchar_t* name;  // registred name
	extern const wchar_t* title; // window title
	
	// window {x , y} 
	extern int y;
	extern int x;
	
	// window {width , height}
	extern size_t width;
	extern size_t height;

	// style to create window with
	extern DWORD style;

	/*
		============ winapi sutff ============ 
	*/

	extern MSG msg; // window messagin variable
	
	extern int n_cmd_show;
	extern HINSTANCE h_instance;

	extern RECT rect;

	extern HWND handle; // window handle
	extern WNDCLASSW cls; // window register class

	extern HDC hdc;
	extern PAINTSTRUCT paint_struct;

	/*
		========== window function's ========== 
	*/

	bool init(HINSTANCE h_instance , int n_cmd_show);

	void destroy();

	// window messages handler
	LRESULT CALLBACK proc(
		HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param
	);

/* 
//  TODO : in futuer
	void on_resize();
	void on_key_pressed();
	void on_mouse_click();
*/

	void process_messages();
	void show();
	void hide();

}
// end : namespace window

#endif
