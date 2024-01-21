
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

#ifndef D2D_H
#define D2D_H
	#include <d2d1.h>
	#include <d2d1_1.h>
	#include <d2d1helper.h>

	#include <d3d9.h> // directx 9
	#include <d3d9types.h>

	#include <dwrite.h>
	#include <wincodec.h>

	#pragma comment(lib, "d2d1.lib")
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

	extern const wchar_t* name;
	extern const wchar_t* title;
	// window {x , y} 
	extern int y;
	extern int x;
	extern float dpi;
	extern size_t style;
	
	// window {width , height}
	extern size_t width;
	extern size_t height;

	extern uint32_t* buffer;
	extern size_t size;

	// winapi sutff
	extern MSG msg; // window messagin variable
	
	extern int n_cmd_show;
	extern HINSTANCE h_instance;

	extern HWND handle; // window handel
	extern WNDCLASS wnd_class; // window register class
	
	extern PAINTSTRUCT paint_struct;
	extern HDC hdc; // handle device context

	// directx stuff
	extern PDIRECT3D9 d3d_interface;
	extern PDIRECT3DDEVICE9 d3d_device;
	extern D3DPRESENT_PARAMETERS d3d_device_info; // device information
	extern D3DCOLOR clear_color;
	extern IDirect3DSurface9* d3d_surface; // d3d buck buffer
	extern RECT rect;

	// method's
	bool init(HINSTANCE h_instance , int n_cmd_show);
	void destroy();

	// window messages handler
	LRESULT CALLBACK proc(
		HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param
	);

	void show();
	void hide();

}
// end : namespace window

#endif
