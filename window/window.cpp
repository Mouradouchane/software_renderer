
#pragma once 

#include "window.hpp"

#ifndef WINDOW_CPP
#define WINDOW_CPP

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int x = 0;
int y = 0;

size_t width  = 800;
size_t height = 600;
size_t size   = window::width * window::height;

DWORD style = NULL;// WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASSW cls = {};

RECT rect;
HDC hdc;
PAINTSTRUCT paint_struct;

// main screen stuff
HMONITOR    h_monitor;
MONITORINFO monitor_info;

/*
    ============= window function's =============
*/

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    // get main monitor info
    h_monitor = MonitorFromWindow(window::handle, MONITOR_DEFAULTTOPRIMARY);

    ZeroMemory(&monitor_info, sizeof(MONITORINFO));
    monitor_info.cbSize = sizeof(MONITORINFO);

    if (!GetMonitorInfoA(h_monitor, &monitor_info)) {
        show_error("error", "failed to get monitor info");
        return false;
    }

    // get monitor/screen resoultion for full-screen window
    window::width  = GetSystemMetrics(SM_CXSCREEN);
    window::height = GetSystemMetrics(SM_CYSCREEN);

    // setup window class 
    window::cls.lpszClassName = window::name;
    window::cls.hInstance = window::h_instance;
    window::cls.style = CS_HREDRAW | CS_VREDRAW;
    window::cls.lpfnWndProc = window::proc;
    window::cls.cbWndExtra = 0;
    window::cls.cbClsExtra = 0;

    // resigster window using class
    if (RegisterClassW(&(window::cls)) == NULL) {
        std::string err = get_last_error_window();
        show_error(
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
        std::string err = get_last_error_window();

        show_error(
            "error", err
        );

        return false;
    }

    // set window to fullscreen
    SetWindowLong(window::handle, GWL_STYLE, window::style);

    if (
        FAILED(
            SetWindowPos(
                window::handle,
                NULL,
                0, 0,
                window::width, 
                window::height,
                SWP_NOSIZE | SWP_NOMOVE |
                SWP_NOZORDER | SWP_NOACTIVATE |
                SWP_FRAMECHANGED
            )
        )
    ) {
        show_error("error", "failed to set window to full-screen mode !");
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

            g_running = false;
            PostQuitMessage(0);

            return 0;
        } 

        case WM_KEYDOWN: {

            wchar_t msg[32];
            OutputDebugStringW(msg);
        
        } break;

        case WM_KEYUP: {

            wchar_t msg[32];
            OutputDebugStringW(msg);

        } break;

        case WM_PAINT: {
            return 0;
        }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);
} 
// end : proc function

}

#endif
