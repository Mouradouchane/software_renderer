

#ifndef WINDOW_HPP 
	#include "window.hpp"
#endif

// #pragma comment (lib,"Gdiplus.lib")

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

float dpi = 0;
size_t width  = 800;
size_t height = 600;
size_t size = window::width * window::height;

size_t style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX );
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASS wnd_class = {};

uint32_t* buffer = nullptr;

PAINTSTRUCT paint_struct;
HDC hdc; 

/*
    directx 9 stuff
*/

PDIRECT3D9 d3d_interface = nullptr; 
PDIRECT3DDEVICE9 d3d_device = nullptr;
IDirect3DSurface9* d3d_surface = nullptr;

D3DPRESENT_PARAMETERS d3d_device_info; // device information
D3DCOLOR clear_color = 0;

RECT rect;

/*
    window method's
*/

bool init(HINSTANCE h_instance , int n_cmd_show) {

    window::buffer = new uint32_t[window::width * window::height];

    // setup window
    window::h_instance = h_instance;
    window::n_cmd_show = n_cmd_show;

    window::wnd_class.style = CS_HREDRAW | CS_VREDRAW;
    window::wnd_class.lpfnWndProc = proc;
    window::wnd_class.hInstance = h_instance;
    window::wnd_class.lpszClassName = window::name;

    // resigster window
    RegisterClass(&wnd_class);

    // create window
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

    if (window::handle == NULL) {
        MessageBoxA(NULL, "failed to create 'window' !", 0, MB_OK);
        return false;
    }

    if (GetWindowRect(window::handle, &window::rect) == false) {
        MessageBoxA(NULL, "failed to get 'window rect' !", 0, MB_OK);
        return false;
    }

    window::hdc = GetDC(window::handle);
    HRESULT hr = S_OK;

    // note : we need both 2d & 3d devices to create "device context"
   
    window::d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);

    // setup d3d_device_info

    ZeroMemory(&window::d3d_device_info, sizeof(D3DPRESENT_PARAMETERS));

    window::d3d_device_info.Windowed = TRUE;    
    
    // swap buffers
    window::d3d_device_info.SwapEffect = D3DSWAPEFFECT_FLIP;
    window::d3d_device_info.BackBufferCount = 1;
    window::d3d_device_info.hDeviceWindow = window::handle;
    // try to specifiy buffer format 
    window::d3d_device_info.BackBufferFormat = D3DFMT_UNKNOWN;

    // enable back-buffer access
    window::d3d_device_info.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

    window::d3d_device_info.BackBufferWidth  = window::width;
    window::d3d_device_info.BackBufferHeight = window::height;

    // create a device using d3d_device_info and 
    hr = d3d_interface->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window::handle ,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING ,
        &window::d3d_device_info,
        &window::d3d_device
    );

    if (FAILED(hr)) {

        if (hr == D3DERR_NOTAVAILABLE) {
            MessageBoxA(
                NULL, 
                "d3d9 create device failed : not avalible !", 
                0, MB_OK
            );
        }

        if (hr == D3DERR_INVALIDCALL) {
            MessageBoxA(
                NULL,
                "d3d9 create device failed : invalid call !",
                0, MB_OK
            );
        }
        else {
            MessageBoxA(
                NULL, 
                "d3d9 create device failed !", 
                0, MB_OK
            );
        }

        return false;
    }

    // get window back-buffer 

    hr = window::d3d_device->GetBackBuffer(
        0 , 
        0 , // back buffer index 
        D3DBACKBUFFER_TYPE_MONO , // not supported in "d3d 9"
        &(window::d3d_surface)
    );

    if (FAILED(hr)) {
        MessageBoxA(NULL, "d3d9 failed to get 'back-buffer' !", 0, MB_OK);
        return false;
    }

    ShowWindow(window::handle , window::n_cmd_show);

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
    if (window::d3d_device != nullptr) {
        window::d3d_device->Release();
    }   
    if (window::d3d_interface != nullptr) {
        window::d3d_interface->Release();
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

        // note : this hold pointer to back-buffer
        D3DLOCKED_RECT lock_rect_rslt; 

        HRESULT hr = D3D_OK;

        // try to lock buffer
        hr = window::d3d_surface->LockRect(
            &lock_rect_rslt ,
            NULL ,
            D3DLOCK_DONOTWAIT
        );
        
        // in case failed to get access to the buffer
        if (FAILED(hr)) {
            return 0;
        }

        // get buffer 
        window::buffer = (uint32_t*)lock_rect_rslt.pBits;

        // clear buffer
        ZeroMemory(window::buffer , window::size);

        // begin the scene
        window::d3d_device->BeginScene();

        // do rendering on the back buffer here
        if (window::buffer != nullptr) {

            for (size_t y = 0; y < window::height; y += 1) {
                for (size_t x = 0; x < window::width; x += 1) {
                    window::buffer[window::width * y + x] = window::clear_color;
                }
            }

        }

        // end the scene
        window::d3d_device->EndScene();
        
        // unlook buffer
        window::d3d_surface->UnlockRect();

        // displays buffer   
        window::d3d_device->Present(NULL, NULL, NULL, NULL);

        return 0;
    }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);

} 
// end : proc function

}

#endif
