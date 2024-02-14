
#include "includes.hpp"

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){


    if ( !window::init(h_instance, n_cmd_show) ) {
        exceptions::show_error("init window error", exceptions::get_last_error_window());
        return GetLastError();
    }
  
    if (!graphics::init()) {
        window::destroy();

        exceptions::show_error("init window error", "failed to init renderer !");
        return 0;
    }

    std::thread fps_update_thread();

    // for preformance counting 
    timer timerr; 
    uint32_t time_ellapse = 0;

    // main loop 
    while( global::running ){

        timerr.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        graphics::render();
        UpdateWindow(window::handle);

        global::frames += 1;
        time_ellapse = timerr.stop();

        // for stable frame's per sec
        if (time_ellapse < global::frame_time) {
            Sleep(global::frame_time - time_ellapse);
        }
    
    }
    // end : main loop 

    // free resources
    graphics::destroy();
    window::destroy();

	return 0;
}
// end : main function
