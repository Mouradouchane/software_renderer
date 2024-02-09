
#pragma once 

#include "window.hpp"

#ifndef WINDOW_CPP
#define WINDOW_CPP

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int x = CW_USEDEFAULT;
int y = CW_USEDEFAULT;

size_t width  = 800;
size_t height = 600;
size_t size   = window::width * window::height;

DWORD style = WS_OVERLAPPEDWINDOW ;
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASSW cls = {};

RECT rect;
HDC hdc;
PAINTSTRUCT paint_struct;

/*
    ============= window function's =============
*/

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    // setup window class 
    window::cls.lpszClassName = window::name;
    window::cls.hInstance = window::h_instance;
    window::cls.style = CS_HREDRAW | CS_VREDRAW;
    window::cls.lpfnWndProc = window::proc;
    window::cls.cbWndExtra = 0;
    window::cls.cbClsExtra = 0;

    // resigster window using class
    if (RegisterClassW(&(window::cls)) == NULL) {
        std::string err = exceptions::get_last_error_window();
        exceptions::show_error(
            "error", err
        );
        
        return false;
    }

    // create window
    window::handle = CreateWindowExW(
        NULL, // optional window styles.
        window::name , // Window class
        window::title,
        window::style, // Window style

        // size and position
        window::x, window::y,
        window::width, window::height,

        NULL,       // Parent window    
        NULL,       // Menu
        window::h_instance,
        NULL        // Additional application data
    );

    if (window::handle == NULL) {
        std::string err = exceptions::get_last_error_window();

        exceptions::show_error(
            "error", err
        );

        return false;
    }

    window::hdc = GetWindowDC(window::handle);

    window::show();
    
    return true;
}

void destroy() {

    // destroy window
    if (window::handle != NULL) {
        UnregisterClassW(window::name, window::h_instance);
        DestroyWindow(window::handle);
    }

}

// handle window messages 
void process_messages() {

    if (GetMessage(&window::msg, NULL, 0, 0) != 0) {
        // note : this handel keys messages
        TranslateMessage(&window::msg);

        // note : this call 'window::proc'
        DispatchMessage(&window::msg);
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

            global::running = false;
            PostQuitMessage(0);

            return 0;
        } 

        case WM_PAINT: {
            return 0;
        }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
} 
// end : proc function

}

#endif
