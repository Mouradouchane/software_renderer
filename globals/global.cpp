
/*

    all the global "variables / functions" should be here

*/

#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include "global.hpp"

/*
    =================================
            global variables
    =================================
*/


// we need it for window time-api 
#pragma comment(lib, "winmm.lib")

bool g_running = true;

// TODO : move them to renderer
std::vector<mesh*>* g_meshes  = nullptr;
std::vector<mesh*>* g_pmeshes = nullptr;

std::string g_models_path = "./models/";
std::initializer_list<std::string> g_obj_files_list = {
    "./models/teapot.obj",
    "./models/bunny.obj",
	/*
	"./models/stanford-bunny.obj",
	"./models/test.obj",
	*/
};

timer main_timer;

uint32_t total_taken_time = 0;
uint32_t render_time = 0;
uint32_t input_time = 0;
uint32_t os_time = 0;

hr_time_point fps_update_time = hr_clock::now();
hr_time_point fps_next_update_time = hr_clock::now();

uint16_t fps = 0;
uint16_t frames = 0;
uint32_t frame_time = 1000 / ((config::max_fps != 0) ? config::max_fps : 1);

std::string error_title = "error";
std::string warn_title  = "warning";
std::string info_title  = "info";

std::string fps_msg  = "FPS : ";
std::string loop_msg = "LOOP TIME : ";

RECT fps_msg_rect = {
	10,  // x
	20,  // y
	400, // w
	50,  // h
};

RECT loop_msg_rect = {
	10,  // x
	40,  // y
	400, // w
	100, // h
};


/*
    =================================
            global functions
    =================================
*/


std::string get_last_error_window() {

    // get last error recorded by win api 
    DWORD error_id = GetLastError();

    // if no error message has been recorded
    if (error_id == 0) return std::string();

    LPSTR message_buffer = nullptr;

    // get error message as string
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_id,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&message_buffer,
        0,
        NULL
    );

    // copy the error message into a std::string
    std::string message(message_buffer, size);

    // free message buffer
    LocalFree(message_buffer);

    return message;
}


void show_error(std::string const& title, std::string const& message, bool sound) {

    if (sound) MessageBeep(MB_ICONERROR);

    int action = 0;
    action = MessageBoxA(
        NULL,
        message.c_str(), // message 
        title.c_str(),  // title
        MB_OK | MB_ICONERROR // box options
    );

    while (action == 0) {
        Sleep(50);
    }

}

void show_warn(std::string const& title, std::string const& message, bool sound) {
    
    if (sound) MessageBeep(MB_ICONWARNING);
    
    int action = 0;
    action = MessageBoxA(
        NULL,
        message.c_str(), // message 
        title.c_str(),  // title
        MB_OK | MB_ICONWARNING // box options
    );

    while (action == 0) {
        Sleep(50);
    }

}


#endif
