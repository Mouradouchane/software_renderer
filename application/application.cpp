
#pragma once 

#ifndef APPLICATION_CPP
#define APPLICATION_CPP

#include "application.hpp"


uint32_t application::init(HINSTANCE h_instance , int n_cmd_show) {

    if (window::init(h_instance, n_cmd_show) == false) {
        
        show_error(error_title, get_last_error_window());
        return INIT_FAILED;
    }

    if (graphics::init() == false) {
        window::destroy();

        show_error(error_title, "failed to init renderer !");
        return INIT_FAILED;
    }

    if (!preformance::init()) {

        show_warn(warn_title, "unexpected error while setuping some preformance threads !");
        return INIT_FAILED;
    }

    return INIT_SUCCESSED;
}


void application::run() {

    periodic_timer fps_pt;

    // main loop 
    while (running) {

        fps_pt.update();
        preformance::main_timer.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        graphics::render();
        UpdateWindow(window::handle);

        // calc time stuff
        preformance::frames += 1;

        if (fps_pt.is_time_for_work()) {
            preformance::fps = preformance::frames;
            preformance::frames = 0;
        }

        preformance::total_taken_time = preformance::main_timer.stop();

        // sleep between frames if needed for stable frame rate
        if (preformance::total_taken_time < preformance::frame_time) {
            Sleep(preformance::frame_time - preformance::total_taken_time);
        }

    }
    // main loop end

}

void application::clean() {

    // free resources
    preformance::destroy();
    graphics::destroy();
    window::destroy();

}


#endif
