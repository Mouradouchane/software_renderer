
#include <windows.h>
#include <time.h>
#include <random>
#include "sdl2/include/SDL.h"

#include "types/types.hpp"

uint32_t width  = 800;
uint32_t height = 600;

uint8_t random(uint8_t range_from, uint8_t range_to);

int WINAPI WinMain(
	HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR p_cmd_line, int n_cmd_show
){

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		MessageBoxA(NULL, "SDL Failed to INIT Because : " + *SDL_GetError(), 0, MB_ICONERROR);
		return 1;
	}
	
	// create window
	SDL_Window* window = SDL_CreateWindow(
		"Software - Renderer", // Title 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // X and Y 
		width , height , // width and height
		0 // flags 
	);

	if (window == NULL) {
		MessageBoxA(NULL, "SDL Failed to Create Window Because : " + *SDL_GetError() , 0, MB_ICONERROR);
		return 1;
	}

	// create renderer 
	SDL_Renderer* renderer = SDL_CreateRenderer( window , -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		MessageBoxA(NULL, "SDL Failed to Create Renderer Because : " + *SDL_GetError() , 0, MB_ICONERROR);
		return 1;
	}

	// get window buffer
	// NOTE : in resize you need to get a new surface !!!!!!!!!!
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	if (window_surface == NULL) {
		MessageBoxA(NULL, "SDL Failed to Get Window Surface Because : " + *SDL_GetError(), 0, MB_ICONERROR);
		return 1;
	}

	bool quit = false;
	SDL_Event sdl_event;

	uint32_t* window_buffer   = (uint32_t*)(window_surface->pixels);
	SDL_Surface* front_buffer = SDL_CreateRGBSurface(0 , width , height , 32 , 0, 0, 0, 0);

	/*
	uint32_t* back_buffer   = new uint32_t[window_surface->w * window_surface->h];
	uint32_t* swap_buffer   = front_buffer;
	*/

	// main loop 
	while ( !quit ) {
		
		while ( SDL_PollEvent(&sdl_event) ) {

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

		// clear old frame
		SDL_RenderClear(renderer);

		// SDL_LockSurface(window_surface);

		uint32_t* buffer = (uint32_t *)front_buffer->pixels;

		// process new frame
		for (size_t y = 0; y < height; y += 1) {
			for (size_t x = 0; x < width; x += 1) {
				buffer[x + (y * width)] = SDL_MapRGB(window_surface->format, x*random(0, 255), y*random(0, 255) , random(0, 255));
			}
		}
		// SDL_UnlockSurface(window_surface);

		SDL_BlitSurface(front_buffer, 0, window_surface, 0);
		if (SDL_UpdateWindowSurface(window) != 0 ) {
			MessageBoxA(NULL, "SDL Failed to Render Buffer Into Window Because : " + *SDL_GetError(), 0, MB_ICONERROR);
			quit = true;
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

uint8_t random(uint8_t min , uint8_t max) {
	/*
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>   distr(range_from, range_to);
	return (uint8_t)distr(generator);
	*/
	std::srand(time(0));
	return (uint8_t)(std::rand() - max + min);

}