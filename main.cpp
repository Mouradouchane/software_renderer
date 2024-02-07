
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

    // main loop 
    while( global::running ){

        // window message + inputs
        window::process_messages();

        // render 
        graphics::render();

        InvalidateRect(window::handle, 0, 0);
        UpdateWindow(window::handle);

        // todo : sleep based on time-elapse
        Sleep(25);
    }

    graphics::destroy();
    window::destroy();

	return 0;
}
// end : main function
