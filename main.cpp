
#ifndef WINDOWS_H
#define WINDOWS_H
    #include <windows.h>
#endif

#ifndef GDI_PLUS_H
#define GDI_PLUS_H
    #include <gdiplus.h>
#endif

#ifndef TIME_H
#define TIME_H
    #include <time.h>
#endif

#ifndef RANDOM_H
#define RANDOM_H
    #include <random>
#endif

#ifndef TYPES_HPP
    #include "types/types.hpp"
#endif

#ifndef WINDOW_HPP 
    #include "window/window.hpp"
#endif

// global variables
bool running;

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

    if (window::init(h_instance, n_cmd_show) == false) {
        MessageBoxA(window::handle , "failed to create window" , 0 , MB_OK | MB_ICONERROR);
        return GetLastError();
    }

    running = true;

    // main loop 
    while (running){

        // handle window messages 
        if (GetMessage(&window::msg, NULL, 0, 0) > 0) {

            // note : this handel keys messages
            TranslateMessage(&window::msg);

            // note : this call 'proc'
            DispatchMessage(&window::msg);

        }

        SendMessage(window::handle, WM_PAINT, 0, 0);
        //Sleep(15);

    }

    window::destroy();

	return 0;
}
// end : main function
