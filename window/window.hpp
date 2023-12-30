

#ifndef WINDOW_H
	#define WINDOW_H
	#include <windows.h>
#endif

#ifndef STD_STRING
	#define STD_STRING
	#include <string>
#endif

#ifndef WINDOW_CLASS_HPP 

#define WINDOW_CLASS_HPP 

typedef LRESULT (CALLBACK *window_proc)(
	HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param
);

class window {

private : 

	std::wstring name = L"default";
	size_t height = 128;
	size_t width = 128;
	size_t x = 10;
	size_t y = 10;
	bool fullscreen = false;
	bool visible = false;

	WNDCLASS wc = { };
	HWND hwnd = NULL;
	HINSTANCE hinst;

	DWORD style = WS_OVERLAPPEDWINDOW;

	/*
		private method's
	*/
	window_proc proc = nullptr;

public :

	MSG msg;
	int n_cmd_show = 0;

	// constructor
	window(
		HINSTANCE hinst , window_proc proc , int n_cmd_show , 
		std::wstring const& name , 
		size_t width , size_t height
	);

	// destructor
	~window();

	// method's
	
	std::wstring get_name( );
	size_t      get_height( );
	size_t      get_width( );
	size_t      get_x( );
	size_t      get_y( );

	void        set_name( std::wstring const& new_name );
	void        set_height( size_t new_height );
	void        set_width ( size_t new_width );
	void        set_x( size_t new_x );
	void        set_y( size_t new_y );

	void        set_proc(window_proc win_proc);

	bool        is_window_created();
	bool		show( );

};

#endif
