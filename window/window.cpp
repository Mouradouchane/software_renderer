
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
WNDCLASSW window_class = {};

// window buffer
uint32_t* buffer = nullptr;

/*
    ============= window function's =============
*/

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    // setup window class 
    window::window_class.lpszClassName = window::name;
    window::window_class.hInstance = window::h_instance;
    window::window_class.style = CS_HREDRAW | CS_VREDRAW;
    window::window_class.lpfnWndProc = window::proc;
    window::window_class.cbWndExtra = 0;
    window::window_class.cbClsExtra = 0;

    // resigster window using class
    if (RegisterClassW(&(window::window_class)) == NULL) {
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

    // allocate buffer
    window::buffer = new uint32_t[800 * 600];

    // setup bitmap
    ZeroMemory(&(window::bitmap), sizeof(BITMAP));
    window::bitmap.bmWidth = window::width;
    window::bitmap.bmHeight = window::height;
    window::bitmap.bmWidthBytes = 4;
    window::bitmap.bmBitsPixel = 32;
    window::bitmap.bmPlanes = 1;
    window::bitmap.bmBits = window::buffer;

    // create hdc for bitmap 
    window::bitmap_hdc = CreateCompatibleDC(window::hdc);

    // just a handle to the bitmap
    window::hbitmap = CreateBitmap(
        window::width ,
        window::height,
        window::bitmap.bmPlanes,
        window::bitmap.bmBitsPixel ,
        window::buffer
    );

    SelectObject(window::bitmap_hdc , window::hbitmap);

    window::show();
    return true;
}

void destroy() {

    // destroy window
    if (window::handle != NULL) {
        UnregisterClassW(window::name, window::h_instance);
        DestroyWindow(window::handle);
    }

    // todo : implement free buffer
    if (window::buffer != nullptr) {
        delete[] window::buffer;
        window::buffer = nullptr;
    }

}

void handle_message() {

    // handle window messages 
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

        // case WM_ERASEBKGND: return 1;

        case WM_PAINT: {
            // renderer::render();
            return 0;
        }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);

} 
// end : proc function

}

#endif
