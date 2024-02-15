
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

    // start thread for "fps_update_routine" 
    global::fps_update_thread = std::thread(
        global::fps_update_worker
    );
    
    // for preformance counting 
    timer gtimer; 

    // main loop 
    while( global::running ){

        gtimer.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        graphics::render();
        UpdateWindow(window::handle);

        global::frames += 1;
        global::taken_time = gtimer.stop();

        // for stable frame's per sec
        if ((global::taken_time + global::time_bais) < global::frame_time) {
            Sleep(global::frame_time - global::taken_time);
        }
    
    }
    // end : main loop 

    // join thread's
    global::fps_update_thread.join();

    // free resources
    graphics::destroy();
    window::destroy();

	return 0;
}
// end : main function
