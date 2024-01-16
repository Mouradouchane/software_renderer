

#ifndef WINDOW_HPP 
	#include "window.hpp"
#endif

#pragma comment (lib,"Gdiplus.lib")

#ifndef WINDOW_CPP

#define WINDOW_CPP

extern bool running;

namespace window{

const wchar_t* name  = L"software_renderer";
const wchar_t* title = L"software - renderer";

int y = CW_USEDEFAULT;
int x = CW_USEDEFAULT;

size_t width  = 800;
size_t height = 600;

size_t style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX );
MSG msg;

int n_cmd_show = 0;
HINSTANCE h_instance;

HWND handle = NULL;
WNDCLASS wnd_class = {};

uint32_t* buffer = nullptr;
gdi::Bitmap* bitmap = nullptr;

gdi::Graphics* renderer = nullptr;
gdi::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken = (ULONG_PTR)nullptr;

PAINTSTRUCT paint_struct;
HDC hdc; 

bool init(HINSTANCE h_instance , int n_cmd_show) {

    buffer = new uint32_t[window::width * window::height];

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
    if (window::handle == NULL) return false;

    // setup & initialize gdi+

    gdi::GdiplusStartup(
        &window::gdiplusToken, 
        &window::gdiplusStartupInput, 
        NULL
    );

    window::hdc = GetDC(window::handle);

    window::renderer = new gdi::Graphics(window::hdc);

    // setup bitmapinfo

    window::bitmap = new gdi::Bitmap(
        window::width , 
        window::height,
        PixelFormat32bppRGB
    );
 
    ShowWindow(window::handle , window::n_cmd_show);

    return true;
}


void destroy() {

    if (window::handle != NULL) {
        gdi::GdiplusShutdown(window::gdiplusToken);
        DestroyWindow(window::handle);
        UnregisterClass(window::name, window::h_instance);
    }

    if (window::bitmap != nullptr) {
        delete window::bitmap;
    }

    if (window::buffer != nullptr) {
        delete[] window::buffer;
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

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0,255*3);

        gdi::Color rcolor;

        BITMAPINFO bmp_info;
        bmp_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmp_info.bmiHeader.biWidth = 800;
        bmp_info.bmiHeader.biHeight = 600;
        bmp_info.bmiHeader.biPlanes = 1;
        bmp_info.bmiHeader.biBitCount = 32;
        bmp_info.bmiHeader.biCompression = BI_RGB, 
        bmp_info.bmiHeader.biSizeImage = 800*600;

        HBITMAP bmp = CreateDIBSection(
            window::hdc,
            &bmp_info,
            DIB_RGB_COLORS,
            (void**)(window::buffer),
            0 , 0
        );
        
        if (buffer == NULL) return 0;

        HDC comp_dc = CreateCompatibleDC(window::hdc);
        HGDIOBJ gdi_obj = SelectObject(comp_dc, bmp);

        for (size_t x = 0; x < window::width; x += 1) {
            for (size_t y = 0; y < window::height; y += 1) {
                //rcolor = gdi::Color(dist6(rng), dist6(rng), dist6(rng));
                window::buffer[(y * window::width + x)] = 0x00FF00;
            }
        }
    
        SetDIBits(
            comp_dc,
            bmp,
            0,
            0,
            (void*)window::buffer,
            &bmp_info , DIB_RGB_COLORS
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
