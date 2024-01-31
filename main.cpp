
#include "includes.hpp"

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

    if ( !window::init(h_instance, n_cmd_show) ) {
        return GetLastError();
    }

    // main loop 
    while( running ){

        window::handle_message();

        // update 

        // render 
        
        // todo : time-elapse fps control 
        SendMessage(window::handle, WM_PAINT, 0, 0);
        Sleep(30);

    }

    window::destroy();

	return 0;
}
// end : main function
