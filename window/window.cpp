
#pragma once 

#include "window.hpp"

// we need directx9 for window buffer access + speed 
#pragma comment(lib, "d3d9.lib")

#ifndef WINDOW_CPP

#define WINDOW_CPP

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int y = CW_USEDEFAULT;
int x = CW_USEDEFAULT;

float  dpi    = 0;
size_t width  = 800;
size_t height = 600;
size_t size   = window::width * window::height;

DWORD style = CS_HREDRAW | CS_VREDRAW | (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME);
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASSW window_class = {};

uint32_t* buffer = nullptr;

// directx 9
namespace d3d {

    PDIRECT3D9 inter_face = nullptr;
    PDIRECT3DDEVICE9 device = nullptr;
    IDirect3DSurface9* surface = nullptr; // d3d buck buffer
    D3DPRESENT_PARAMETERS device_info = { 0 }; // device information
    D3DLOCKED_RECT lock_rect_rslt = { 0 };
    RECT rect = { 0 };
    D3DCOLOR clear_color = 0;

}

/*
    ============= function's =============
*/


namespace { // private functions 

    bool init_window() {

        // setup window
        window::window_class.lpszClassName = window::name;
        window::window_class.hInstance     = window::h_instance;
        window::window_class.style         = CS_GLOBALCLASS;
        window::window_class.lpfnWndProc   = window::proc;

        // resigster window
        if (RegisterClassW(&(window::window_class)) == NULL) {
            
            std::string err = exceptions::get_last_error_window();
            
            exceptions::show_error(
                "window register error", err
            );
            return false;
        }

        // create window
        window::handle = CreateWindowExW(
            NULL , // optional window styles.
            window::name,  // Window class
            window::title, // Window text
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
                "create window error", err
            );
            return false;
        }

        if (!GetWindowRect(window::handle, &window::d3d::rect)) {

            std::string err = exceptions::get_last_error_window();

            exceptions::show_error(
                "window rect error", err
            );
            return false;
        }

        return true;
    }

    bool init_d3d() {

        HRESULT hr = S_OK;
        // note : we need both 2d & 3d devices to create "device context"

        window::d3d::inter_face = Direct3DCreate9(D3D_SDK_VERSION);

        // setup d3d_device_info

        ZeroMemory(&window::d3d::device_info, sizeof(D3DPRESENT_PARAMETERS));

        window::d3d::device_info.Windowed = TRUE;
        // swap buffers
        window::d3d::device_info.SwapEffect = D3DSWAPEFFECT_FLIP;
        window::d3d::device_info.BackBufferCount = 1;
        window::d3d::device_info.hDeviceWindow = window::handle;
        // try to specifiy buffer format 
        window::d3d::device_info.BackBufferFormat = D3DFMT_UNKNOWN;

        // enable back-buffer access
        window::d3d::device_info.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

        window::d3d::device_info.BackBufferWidth = window::width;
        window::d3d::device_info.BackBufferHeight = window::height;

        // create a device using d3d_device_info and 
        hr = d3d::inter_face->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            window::handle,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &window::d3d::device_info,
            &window::d3d::device
        );

        // TODO : error handling
        if ( FAILED(hr) ) { 

            std::string err = exceptions::get_last_error_window();

            exceptions::show_error(
                "d3d9 create device error", err
            );
            return false;
        }

        // get window back-buffer 

        hr = window::d3d::device->GetBackBuffer(
            0,
            0, // back buffer index 
            D3DBACKBUFFER_TYPE_MONO, // not supported in "d3d 9"
            &(window::d3d::surface)
        );

        if ( FAILED(hr) ) {

            std::string err = exceptions::get_last_error_window();

            exceptions::show_error(
                "d3d9 get back buffer error", err
            );
            return false;
        }

        return true;
    }

}

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    if ( !init_window() ) return false;
    if ( !init_d3d() )    return false;

    window::show();
    return true;
}


void destroy() {

    // free window stuff

    if (window::handle != NULL) {
        UnregisterClassW(window::name, window::h_instance);
        DestroyWindow(window::handle);
    }

    if (window::buffer != nullptr) {
        delete[] window::buffer;
        window::buffer = nullptr;
    }

    // free Direct3D stuff
    
    if (window::d3d::inter_face != nullptr) {
        window::d3d::inter_face->Release();
    }

    if (window::d3d::device != nullptr) {
        window::d3d::device->Release();
    }

    if (window::d3d::surface != nullptr) {
        window::d3d::surface->Release();
    }

}

void handle_message() {

    // handle window messages 
    if (GetMessage(&window::msg, NULL, 0, 0) > 0) {

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

bool lock_buffer() {

    HRESULT hr = D3D_OK;

    // try to lock d3d buffer
    hr = window::d3d::surface->LockRect(
        &(window::d3d::lock_rect_rslt),
        NULL,
        D3DLOCK_DONOTWAIT
    );

    if (FAILED(hr)) return false;
    
    return true;
}

bool unlock_buffer() {

    // try to unlock d3d buffer
    LRESULT hr = window::d3d::surface->UnlockRect();

    if (FAILED(hr)) return false;
    
    return true;
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

        if ( window::lock_buffer() ) {
            // get pointer to the buffer 
            window::buffer = (uint32_t*)window::d3d::lock_rect_rslt.pBits;
        }
        else return 0;

        // clear buffer
        ZeroMemory(window::buffer , window::size);

        // begin the scene
        BeginPaint(window::handle, 0);
        window::d3d::device->BeginScene();

        // do rendering here


        // end the scene
        window::d3d::device->EndScene();
        EndPaint(window::handle, 0);
        
        // unlook buffer
        window::unlock_buffer();

        // displays buffer   
        window::d3d::device->Present(NULL, NULL, NULL, NULL);

        return 0;
    }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);

} 
// end : proc function

}

#endif
