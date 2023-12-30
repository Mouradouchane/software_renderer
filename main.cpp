
#include <windows.h>
#include "window/window.hpp"

LRESULT CALLBACK win_proc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
);

int WINAPI wWinMain(
	HINSTANCE h_instance , HINSTANCE h_prev_instance , PWSTR p_cmd_line , int n_cmd_show
) {

	// the main loop
	
	bool running = true;
	window main_window(h_instance , win_proc, n_cmd_show , L"software - renderer" , 800 , 600);
	
	if (main_window.is_window_created() == false) {
		MessageBox(0, L"window creation error !", 0, MB_OK);
		return 0;
	}

	while( running ) {
			
		// process input

		// update

		// render

		// process window
		if( GetMessage( &(main_window.msg) , NULL, 0, 0) > 0 ) {

			TranslateMessage( &(main_window.msg) );
			DispatchMessage ( &(main_window.msg) );
			
		}

	}

	
	return 0;

}


LRESULT CALLBACK win_proc (
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
){

	switch (uMsg) {

		case WM_DESTROY: {

			PostQuitMessage(0);
			ExitProcess(0);
			return 0;
	
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);

			return 0;
		} 

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}