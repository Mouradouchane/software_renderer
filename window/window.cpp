
#pragma once 

#ifndef WINDOW_HPP 
	#include "window.hpp"
#endif

#ifndef WINDOW_CPP

#define WINDOW_CPP

extern bool running;
extern uint8_t random8(uint8_t min = 0, uint8_t max = UINT8_MAX);
extern uint32_t random32(uint32_t min = 0, uint32_t max = UINT32_MAX);

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int y = CW_USEDEFAULT;
int x = CW_USEDEFAULT;

float  dpi    = 0;
size_t width  = 800;
size_t height = 600;
size_t size   = window::width * window::height;

DWORD style = WS_OVERLAPPEDWINDOW;
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASSW window_class = {};

uint32_t* buffer = nullptr;

// PAINTSTRUCT paint_struct;
// HDC hdc; 

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
std::string get_last_error_string(){

    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}

namespace { // private functions 

    bool init_window() {

        // setup window
        window::window_class.lpszClassName = window::name;
        window::window_class.hInstance     = window::h_instance;
        window::window_class.style         = window::style;
        window::window_class.lpfnWndProc   = window::proc;

        // resigster window
        RegisterClassW( &window::window_class );

        // create window
        window::handle = CreateWindowEx(
            NULL, // optional window styles.
            window::name,  // Window class
            window::title, // Window text
            WS_OVERLAPPEDWINDOW, // Window style

            // size and position
            window::x, window::y,
            window::width, window::height,

            NULL,       // Parent window    
            NULL,       // Menu
            window::h_instance,
            NULL        // Additional application data
        );

        if (window::handle == NULL) {
            std::string err = get_last_error_string();
            MessageBoxA(NULL, err.c_str() , 0, MB_OK);
            return false;
        }

        if (!GetWindowRect(window::handle, &window::d3d::rect)) {
            MessageBoxA(NULL, "failed to get 'window rect' !", 0, MB_OK);
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

            switch (hr) {

                case D3DERR_NOTAVAILABLE: { } break;

                case D3DERR_INVALIDCALL: { } break;

                default : { } break;

            }

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

            // TODO : handle errors
            
            return false;
        }

        return true;
    }

}

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    if ( !init_window() ) return false;
    if ( !init_d3d() ) return false;

    window::show();
    return true;
}


void destroy() {

    // free window stuff
    if (window::handle != NULL) {
        DestroyWindow(window::handle);
        UnregisterClass(window::name, window::h_instance);
    }

    if (window::buffer != nullptr) {
        delete[] window::buffer;
    }

    // free Direct3D stuff
    if (window::d3d::device != nullptr) {
        window::d3d::device->Release();
    }   

    if (window::d3d::inter_face != nullptr) {
        window::d3d::inter_face->Release();
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

    if (FAILED(hr)) {
        // TODO : handle errors
        return false;
    }
    
    return true;
}

bool unlock_buffer() {

    // try to unlock d3d buffer
    LRESULT hr = window::d3d::surface->UnlockRect();

    if (FAILED(hr)) {
        // TODO : handle error -> "invalid call" only
        return false;
    }
    
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
        window::d3d::device->BeginScene();

        // do rendering here


        // end the scene
        window::d3d::device->EndScene();
        
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
