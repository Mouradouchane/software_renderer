
/*
	=================================================
	program window and it's props here in 'namespace' 
	=================================================
*/

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <windows.h>
#endif

#ifndef TYPES_HPP
	#include "../types/types.hpp"
#endif

#ifndef WINDOW_HPP

#define WINDOW_HPP

namespace window {

	// window main handler
	LRESULT CALLBACK proc(
		HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param
	);
		
	extern const wchar_t* name;
	extern const wchar_t* title;
	// window {x , y} 
	extern int y;
	extern int x;

	extern size_t style;
	
	// window {width , height}
	extern size_t width;
	extern size_t height;
	
	extern MSG msg; // window messagin variable
	
	extern int n_cmd_show;
	extern HINSTANCE h_instance;

	extern HWND handle; // window handel
	extern WNDCLASS wnd_class; // window register class

	extern PAINTSTRUCT paint_struct;
	extern HDC hdc; // handle device context

	// window initializer
	bool init(HINSTANCE h_instance , int n_cmd_show);
	void destroy();

	void show();
	void hide();


}
// end : namespace window

#endif
