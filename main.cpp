

#include <windows.h>
#include "window/window.hpp"
#include "types/types.hpp"


LRESULT CALLBACK win_proc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
);

window * main_window = nullptr;

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

	vec2d v2(1.54f, 0.6589f);
	vec3d v3(1.54, 0.6589, 789.45);
	vec4d v4(1.54, 0.6589, 789.45 , 1.111232);

	vector2d v2arr = { 32.2 , 359.45 };
	vector3d v3arr = { 32.2 , 359.45 , 459.5689 };
	vector4d v4arr = { 32.2 , 359.45 , 89.99901 , 0.54};

	// the main loop

	main_window = new window(h_instance , n_cmd_show , "software - renderer" , 800 , 600);
	bool running = true;
	
	if (main_window->is_window_created() == false) {
		MessageBoxA(0, "window creation error !", 0, MB_OK);
		return 0;
	}

	while( running ) {
			
		// process input

		// update

		// render

		// process window
		if( GetMessage( &(main_window->msg) , NULL, 0, 0) > 0 ) {

			TranslateMessage( &(main_window->msg) );
			DispatchMessage ( &(main_window->msg) );
			
		}

		main_window->send_update_message();

	}

	delete main_window;
	return 0;

}

