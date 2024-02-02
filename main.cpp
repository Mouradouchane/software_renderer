
#include "includes.hpp"

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

    if ( !window::init(h_instance, n_cmd_show) ) {
        exceptions::show_error("init window error", exceptions::get_last_error_window());
        return GetLastError();
    }

    if (!renderer::init()) {
        window::destroy();

        exceptions::show_error("init window error", "failed to init renderer !");
        return GetLastError();
    }

    // main loop 
    while( global::running ){

        // window message + inputs
        window::handle_message();

        // update 

        // render 
        renderer::render();

        // todo : time-elapse fps control 
        Sleep(30);

    }

    renderer::destroy();
    window::destroy();

	return 0;
}
// end : main function
