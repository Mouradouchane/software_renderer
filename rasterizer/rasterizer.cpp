// rasterizer.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "rasterizer.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"rasterizer\0"; // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING] = L"rasterizer\0"; // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        LPWSTR    lpCmdLine,
    _In_        int       nCmdShow
) {
    nCmdShow = SW_MAXIMIZE;
    std::srand(time(0));

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RASTERIZER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd) return FALSE;
    

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RASTERIZER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)) {

 
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            if (msg.message == WM_QUIT) return msg.message;
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            /*
            msg.message = WM_PAINT;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            */
        }

        //InvalidateRect(hWnd, NULL, FALSE);
    }

    return (int) msg.wParam;
}


//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RASTERIZER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RASTERIZER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}



//  PURPOSE: Processes messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
   
    switch ( message ) {

    case WM_COMMAND : {

        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

    } break;
    /*
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, FALSE);
    break;
    */

    case WM_PAINT : {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        COLORREF bcolor = 0x00000;
        COLORREF color = 0x00ff00;
            
        FillRect(hdc, &ps.rcPaint , (HBRUSH)(COLOR_WINDOW + 4) );

        for (int x = 100; x <= 399 ; x += 1) {
            for (int y = 100; y <= (std::rand() % (300 + 1)) ; y += 2) {
                SetPixel(hdc, x+2, y, color);
                SetPixel(hdc, x-2, y, color);
                SetPixel(hdc, x, y, color);
            }
        }

        EndPaint(hWnd, &ps);
        InvalidateRect(hWnd, NULL, FALSE);
        
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);

    } // end of switch 

    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
