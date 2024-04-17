
#include "includes.hpp"

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

    if ( !window::init(h_instance, n_cmd_show) ) {
        exceptions::show_error(error_title, exceptions::get_last_error_window());
        return GetLastError();
    }
  
    if ( !graphics::init() ) {
        window::destroy();

        exceptions::show_error(error_title, "failed to init renderer !");
        return 0;
    }

    if ( !preformance::init() ) {
        exceptions::show_warn(warn_title, "unexpected error while setuping some preformance threads !");
    }
  
    models = files::load_3d_models( models_path );

    periodic_timer fps_pt;

    // main loop 
    while( running ){

        fps_pt.update();
        preformance::main_timer.start();

        // window message + inputs
        window::process_messages();

        // rendering
        InvalidateRect(window::handle, 0, 0);
        graphics::render();
        UpdateWindow(window::handle);

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
    // end : main loop

    // free resources
    preformance::destroy();
    graphics::destroy();
    window::destroy();

	return 0;
}
// end : main function
