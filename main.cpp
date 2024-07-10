
#include "includes.hpp"

int WINAPI wWinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, PWSTR p_cmd_line, int n_cmd_show
){

    if ( application::init(h_instance , n_cmd_show) == INIT_FAILED ) {
    
        return EXIT_FAILURE;
    }
   
    application::run();

    application::clean();

	return EXIT_SUCCESS;
}

