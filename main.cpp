
#include "includes.hpp"

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

    if ( !window::init(h_instance, n_cmd_show) ) {
        exceptions::show_error(global::error_title, exceptions::get_last_error_window());
        return GetLastError();
    }
  
    if ( !graphics::init() ) {
        window::destroy();

        exceptions::show_error(global::error_title, "failed to init renderer !");
        return 0;
    }

    if ( !preformance::init() ) {
        exceptions::show_warn(global::warn_title, "unexpected error while setuping some preformance threads !");
    }
  
    // main loop 
    while( global::running ){

        preformance::main_timer.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        graphics::render();
        UpdateWindow(window::handle);

        preformance::frames_counter += 1;
        preformance::taken_time = preformance::main_timer.stop();

        // check if we have time for sleep
        if (preformance::taken_time < preformance::frame_time) {
            Sleep(preformance::frame_time - preformance::taken_time);
        }
    
    }
    // end : main loop 

    // free resources
  
    // includes "thread's join"
    preformance::destroy();

    graphics::destroy();
    window::destroy();

	return 0;
}
// end : main function
