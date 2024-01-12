
#include <windows.h>
#include "sdl2/include/SDL.h"

#include "types/types.hpp"


int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		MessageBoxA(NULL, "SDL Failed to INIT Because : " + *SDL_GetError(), 0, MB_ICONERROR);
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Software - Renderer", // Title 
		20, 20,     // X and Y 
		800, 600, // width and height
		0 // flags 
	);

	if (window == NULL) {
		MessageBoxA(NULL, "SDL Failed to Create Window Because : " + *SDL_GetError() , 0, MB_ICONERROR);
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer( window , -1, SDL_RENDERER_SOFTWARE);

	if (renderer == NULL) {
		MessageBoxA(NULL, "SDL Failed to Create Renderer Because : " + *SDL_GetError() , 0, MB_ICONERROR);
		return 1;
	}

	bool quit = false;
	SDL_Event sdl_event;

	// main loop 
	while ( !quit ) {
		
		if (SDL_PollEvent(&sdl_event)) {

		switch (sdl_event.type) {
			
			case SDL_QUIT: {
				quit = true;
			} break;

			case SDL_WINDOWEVENT: {

				switch (sdl_event.window.event) {

					case SDL_WINDOWEVENT_CLOSE: {
						quit = true;
					} break;

				}

			} break;

		}

		}
	
	}

	// free sdl stuff
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Shuts down all SDL subsystems 
	SDL_Quit();

	return 0;
}
// end : main function

