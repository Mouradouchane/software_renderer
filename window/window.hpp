
/*
	==============================================
	renderer window class for handling main window
	==============================================
*/

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

class window {

private:

	std::string name = "default";

	size_t x = 10;
	size_t y = 10;

	size_t height = 128;
	size_t width = 128;

	bool fullscreen = false;
	bool visible = false;

	WNDCLASSW wc = { };
	HWND hwnd = NULL;
	HINSTANCE hinst;

	DWORD style = WS_OVERLAPPEDWINDOW;

	BITMAPINFO frame_bitmap_info;
	HBITMAP frame_bitmap = 0;
	HDC frame_device_context = 0;

	PAINTSTRUCT paint_struct;

	WNDPROC ptr_proc = nullptr;

public:

	MSG msg;
	int n_cmd_show = 0;

	// constructor
	window(
		HINSTANCE hinst, int n_cmd_show,
		std::string const& name,
		size_t width, size_t height
	);

	// destructor
	~window();

	// method's

	std::string get_name();
	size_t      get_height();
	size_t      get_width();
	size_t      get_x();
	size_t      get_y();

	void        set_name(std::string const& new_name);
	void        set_height(size_t new_height);
	void        set_width(size_t new_width);
	void        set_x(size_t new_x);
	void        set_y(size_t new_y);

	// todo : setup draw "pixels or bitmaps" to the window buffer
	void        setup_bitmap_context();
	void        send_update_message();

	void        on_paint();
	void        on_resize();

	LRESULT CALLBACK proc(
		HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
	);
	
	void        set_proc(WNDPROC win_proc);

	bool        is_window_created( );
	bool        destroy( );

	bool		show( );
	bool        hide( );

};

#endif
