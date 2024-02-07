// d3dtest.cpp : Defines the entry point for the application.
//

/*
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif 
*/

#include "framework.h"
#include "d3dtest.h"

#include <random>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <wincon.h>
#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd = NULL;
bool running = true;
size_t* buffer = new size_t[800 * 600];
MSG msg;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

FLOAT clear_color = 0;

BITMAP  bmp;
HBITMAP bmp_h;
HDC     bmp_dc;

HDC hdc;
PAINTSTRUCT ps;

HRESULT hr = S_OK;

HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

bool getdc = false;

auto start = std::chrono::steady_clock::now();
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double, std::milli> elapse_time;

std::string elapse_time_is = "elapse time is : ";
std::string time_str = "";

bool InitD3D(HWND hWnd){

    ZeroMemory(&bmp, sizeof(BITMAP));

    bmp.bmWidth = 800;
    bmp.bmHeight = 600;
    bmp.bmWidthBytes = 4;
    bmp.bmBitsPixel = 32;
    bmp.bmPlanes = 1;
    bmp.bmBits = buffer;

    return true;
}

// this is the function used to render a single frame
void RenderFrame( ){
    size_t r;

    ZeroMemory(buffer, 800 * 600);

    r = std::rand() * std::rand();

    for (size_t y = 0; y < bmp.bmHeight; y += 1) {
        for (size_t x = 0; x < bmp.bmWidth; x += 1) {
            buffer[800 * y + x] = (x*y) * r;
        }
    }

    if (!getdc) {
        hdc    = GetWindowDC(hWnd);
        bmp_dc = CreateCompatibleDC(hdc);
        bmp_h  = CreateBitmap(bmp.bmWidth, bmp.bmHeight, bmp.bmPlanes, bmp.bmBitsPixel, buffer);
        getdc = true;
    }

    SetBitmapBits(bmp_h, sizeof(size_t) * 800 * 600, buffer);
    SelectObject(bmp_dc, bmp_h);

    BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, bmp_dc, 0, 0, SRCCOPY);

    if (!getdc) {
       // EndPaint(hWnd, &ps);
    }
}


int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow
){
    std::srand(time(0));

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_D3DTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow)){
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DTEST));

    if( ! InitD3D(hWnd) ) return 0;

    if ( !AttachConsole(ATTACH_PARENT_PROCESS)) {
        if ( !AllocConsole() ) return 0;
    }


    if( FAILED(AllocConsole()) ) return false;

    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (console_handle == INVALID_HANDLE_VALUE) return 0;

    // main message loop
    while (running) {

        if(GetMessage(&msg, nullptr, 0, 0) != 0) {

            if ( !TranslateAccelerator(msg.hwnd, hAccelTable, &msg) ){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }

        start = std::chrono::high_resolution_clock::now();
        RenderFrame();
        end = std::chrono::high_resolution_clock::now();

        InvalidateRect(hWnd, 0, 0);
        UpdateWindow(hWnd);

        elapse_time = end - start;
        time_str = std::to_string(elapse_time.count());
        // std::cout << "elapse time is : " << elapse_time.count() << '\n';
        WriteConsoleA(console_handle, elapse_time_is.c_str(), elapse_time_is.size(), 0, 0);
        WriteConsoleA(console_handle, time_str.c_str(), time_str.size(), 0, 0);
        WriteConsoleA(console_handle, "\n", 1, 0, 0);

        Sleep(30);

    }

    FreeConsole();
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_D3DTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(
        szWindowClass,
        szTitle, 
        WS_OVERLAPPEDWINDOW,
        0, 0, 800 , 600, 
        nullptr, nullptr, 
        hInstance, nullptr
   );

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_TIMER: {

    } break;

    case WM_PAINT:{


    } break;

    case WM_DESTROY: {

        running = false;
        PostQuitMessage(0);
       
    } break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
