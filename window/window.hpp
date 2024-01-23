
/*
	=================================================
	program window and it's props here in 'namespace' 
	=================================================
*/

#pragma once 

#ifndef UNICODE
	#define UNICODE
#endif

#ifndef WINDOWS_H
#define WINDOWS_H
	#include <windows.h>
#endif

#ifndef D3D_H
#define D3D_H
	// directx 9
	#include <d3d9.h> 
	#include <d3d9types.h>

	#pragma comment(lib, "d3d9.lib")
#endif

#ifndef RANDOM_H
#define RANDOM_H
	#include <random>
#endif

#ifndef TYPES_HPP
	#include "../types/types.hpp"
#endif

#ifndef WINDOW_HPP

#define WINDOW_HPP

namespace window {

	extern const wchar_t* name;  // registred name
	extern const wchar_t* title; // window title
	
	// window {x , y} 
	extern int y;
	extern int x;
	
	// window {width , height}
	extern size_t width;
	extern size_t height;

	extern float dpi;
	extern DWORD style;

	extern uint32_t* buffer;
	extern size_t size;

	/*
		============ winapi sutff ============ 
	*/

	extern MSG msg; // window messagin variable
	
	extern int n_cmd_show;
	extern HINSTANCE h_instance;

	extern HWND handle; // window handel
	extern WNDCLASSW window_class; // window register class
	
	// extern PAINTSTRUCT paint_struct;
	// extern HDC hdc; // handle device context
	
	/*
		=========== directx variables ===========
	*/
	namespace d3d {

		extern PDIRECT3D9 inter_face;
		extern PDIRECT3DDEVICE9 device;
		extern D3DPRESENT_PARAMETERS device_info; // device information
		extern D3DCOLOR clear_color;
		extern IDirect3DSurface9* surface; // d3d buck buffer
		extern D3DLOCKED_RECT lock_rect_rslt; 
		extern RECT rect;

	}

	/*
		========== window function's ========== 
	*/

	bool init(HINSTANCE h_instance , int n_cmd_show);

	void destroy();
	void destroy_resource();

	// window messages handler
	LRESULT CALLBACK proc(
		HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param
	);

	bool lock_buffer();
	bool unlock_buffer();

	void on_resize();

	void show();
	void hide();

}
// end : namespace window

#endif
