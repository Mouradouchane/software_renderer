

#ifndef WINDOW_HPP 
	#include "window.hpp"
#endif

#ifndef WINDOW_CPP

#define WINDOW_CPP

extern bool running;

namespace window{

const wchar_t* name = L"software_renderer";
const wchar_t* title = L"software - renderer";

int y = CW_USEDEFAULT;
int x = CW_USEDEFAULT;

size_t width  = 800;
size_t height = 600;

size_t style = WS_OVERLAPPEDWINDOW;
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASS wnd_class = {};

PAINTSTRUCT paint_struct;
HDC hdc; 

bool init(HINSTANCE h_instance , int n_cmd_show) {

    // setup 
    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    wnd_class.lpfnWndProc = proc;
    wnd_class.hInstance = h_instance;
    wnd_class.lpszClassName = window::name;

    // resigster  
    RegisterClass(&wnd_class);

    // create
    window::handle = CreateWindowEx(
        0, // Optional window styles.
        window::name , // Window class
        window::title, // Window text
        window::style, // Window style

        // Size and position
        window::x , window::y, 
        window::width , window::height,

        NULL,       // Parent window    
        NULL,       // Menu
        window::h_instance ,
        NULL        // Additional application data
    );

    // failed to create window
    if (window::handle == NULL) return false;

    ShowWindow(window::handle , window::n_cmd_show);

    return true;
}


void destroy() {

    if (window::handle != NULL) {
        DestroyWindow(window::handle);
        UnregisterClass(window::name, window::h_instance);
    }

}

void show() {

    if (window::handle != NULL) {
        ShowWindow(window::handle, window::n_cmd_show);
    }

}

LRESULT CALLBACK proc(
    HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param
){
    switch (u_msg) {

    case WM_DESTROY: {

        running = false;
        PostQuitMessage(0);

        return 0;
    }

    case WM_PAINT: {

        window::hdc = BeginPaint(window::handle, &window::paint_struct);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(
            hdc, &window::paint_struct.rcPaint, 
            (HBRUSH)(BLACK_BRUSH)
        );

        EndPaint(window::handle, &window::paint_struct);

        return 0;
    }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);

} 
// end : proc function

}

#endif
