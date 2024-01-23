
#ifndef WINDOWS_H
#define WINDOWS_H
    #include <windows.h>
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
    while( running ){

        // handle window messages 
        if (GetMessage(&window::msg, NULL, 0, 0) > 0) {

            // note : this handel keys messages
            TranslateMessage(&window::msg);

            // note : this call 'window::proc'
            DispatchMessage(&window::msg);

        }

        SendMessage(window::handle, WM_PAINT, 0, 0);
        Sleep(30);

    }

    window::destroy();

	return 0;
}
// end : main function

// todo : move this to math library
uint32_t random32(uint32_t min = 0, uint32_t max = UINT32_MAX) {

    // kind of heavy
    /*
    std::random_device random_device;
    std::mt19937 engine(random_device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return (uint32_t)dist(engine);
    */
    return (uint32_t)(std::rand() * (max - min) + max);

}

uint8_t random8(uint8_t min = 0, uint8_t max = UINT8_MAX) {
    
    // kind of heavy
    /*
    std::random_device random_device;
    std::mt19937 engine(random_device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    
    return (uint8_t)dist(engine);
    */

    return (uint8_t)(std::rand() * (max - min) + max);
}