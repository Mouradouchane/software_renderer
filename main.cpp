
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

    window::buffer = new uint32_t[800 * 600];

    // main loop 
    while( global::running ){

        // window message + inputs
        window::handle_message();

        // render 
        renderer::render();

        // todo : time-elapse fps control 
        SendMessageA(window::handle, WM_PAINT, 0, 0);
        Sleep(15);

    }

    renderer::destroy();
    window::destroy();

	return 0;
}
// end : main function
