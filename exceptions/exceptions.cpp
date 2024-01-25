
#pragma once

#include "exceptions.hpp"

#ifndef EXCEPTION_CPP

#define EXCEPTION_CPP

namespace exceptions {

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
        FORMAT_MESSAGE_IGNORE_INSERTS ,
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
        title.c_str() ,  // title
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

}
// end : namespace exceptions

#endif