

#ifndef WINDOW_HPP 
	#include "window.hpp"
#endif

// #pragma comment (lib,"Gdiplus.lib")

#ifndef WINDOW_CPP

#define WINDOW_CPP

extern bool running;

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int y = CW_USEDEFAULT;
int x = CW_USEDEFAULT;

float dpi = 0;
size_t width  = 800;
size_t height = 600;


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
D3DPRESENT_PARAMETERS d3d_device_info; // device information

D3DCOLOR clear_color = 0;

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

    // failed to create window
    if (window::handle == NULL) {
        MessageBoxA(NULL, "failed to create window !", 0, MB_OK);
        return false;
    }

    window::hdc = GetDC(window::handle);

    // 1 - Initialize device-indpendent resources, such
    // as the Direct2D factory.
    ID2D1Factory* factory;
    
    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED , &factory
    );

    // 2 - Create Device Resources 
    RECT rect; GetClientRect(window::handle, &rect);

    D2D1_SIZE_U size = D2D1::SizeU(
        rect.right  - rect.left ,
        rect.bottom - rect.top
    );

    ID2D1HwndRenderTarget* renderer_target;

    // Create a Direct2D render target.
    hr = factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(window::handle, size),
        &renderer_target
    );

    // note : we need both 2d & 3d devices to create "device context"
   
    window::d3d_interface = Direct3DCreate9(D3D_SDK_VERSION);

    // setup d3d_device_info
    
    ZeroMemory(&window::d3d_device_info, sizeof(D3DPRESENT_PARAMETERS));

    window::d3d_device_info.Windowed = TRUE;    
    // swap buffers
    window::d3d_device_info.SwapEffect = D3DSWAPEFFECT_DISCARD; 
    window::d3d_device_info.hDeviceWindow = window::handle;   
    
    // create a device using d3d_device_info and 
    hr = d3d_interface->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window::handle ,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &window::d3d_device_info,
        &window::d3d_device
    );

    if (FAILED(hr)) {
        MessageBoxA(NULL, "d3d9 create device failed !", 0, MB_OK);
        return 0;
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
    


        // clear the window buffer
        window::d3d_device->Clear(
            0, NULL, D3DCLEAR_TARGET, window::clear_color , 1.0f, 0
        );

        // begins the 3D scene
        window::d3d_device->BeginScene();

        // do 3D rendering on the back buffer here

        // ends the 3D scene
        window::d3d_device->EndScene();

        // displays the created frame    
        window::d3d_device->Present(NULL, NULL, NULL, NULL);

        return 0;
    }

    }

    return DefWindowProc(hwnd, u_msg, w_param, l_param);

} 
// end : proc function

}

#endif
