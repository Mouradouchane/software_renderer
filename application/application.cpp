
#pragma once 

#ifndef APPLICATION_CPP
#define APPLICATION_CPP

#include "application.hpp"

uint32_t application::init(HINSTANCE h_instance , int n_cmd_show) {

    if (loader::load_models() != OPEN_OBJ_SUCCESS) {
        return INIT_FAILED;
    }

    if (window::init(h_instance, n_cmd_show) == false) {
        
        show_error(error_title, get_last_error_window());
        return INIT_FAILED;
    }

    if (renderer::init() == false) {
        window::destroy();

        show_error(error_title, "failed to init renderer !");
        return INIT_FAILED;
    }

    if (preformance::init() == false) {

        show_warn(warn_title, "unexpected error while setuping some preformance threads !");
        return INIT_FAILED;
    }

    return INIT_SUCCESSED;
}


void application::run() {

    periodic_timer fps_pt;

    // main loop 
    while (g_running) {

        fps_pt.update();
        main_timer.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        renderer::render();
        UpdateWindow(window::handle);

        // calc time stuff
        frames += 1;

        if (fps_pt.is_time_for_work()) {
            fps = frames;
            frames = 0;
        }

        total_taken_time = main_timer.stop();

        // sleep between frames if needed for stable frame rate
        if (total_taken_time < frame_time) {
            Sleep(frame_time - total_taken_time);
        }

    }
    // main-loop end

}


void application::clean() {

    // free resources
    preformance::destroy();
    renderer::destroy();
    window::destroy();

}


#endif
