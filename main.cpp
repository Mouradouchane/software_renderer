
#include <windows.h>
#include <time.h>
#include <random>
#include "sdl2/include/SDL.h"

#include "types/types.hpp"

uint32_t width  = 800;
uint32_t height = 600;

uint8_t random(uint8_t range_from, uint8_t range_to);
uint32_t random32(uint32_t min, uint32_t max);

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

	// get window buffer
	// NOTE : in resize you need to get a new surface !!!!!!!!!!
	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	// create renderer 
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer( window_surface );

	if (renderer == NULL) {
		MessageBoxA(NULL, "SDL Failed to Create Renderer Because : " + *SDL_GetError() , 0, MB_ICONERROR);
		return 1;
	}


	if (window_surface == NULL) {
		MessageBoxA(NULL, "SDL Failed to Get Window Surface Because : " + *SDL_GetError(), 0, MB_ICONERROR);
		return 1;
	}

	bool quit = false;
	SDL_Event sdl_event;

	uint32_t* window_buffer = (uint32_t*)(window_surface->pixels);

	uint32_t* front = new uint32_t[ width * height ];
	uint32_t* back  = new uint32_t[width * height];


	// core loop 
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

		// lock surface buffer
		SDL_LockSurface(window_surface);

		// process new frame
		for (size_t y = 0; y < height; y += 1) {
			size_t  Y = (y * width);
			for (size_t x = 0; x < width; x += 1) {
				front[Y + x] = SDL_MapRGB(window_surface->format, x * random(0, 255), x * y * random(0, 255), random(0, 255));
				back[Y + x] = SDL_MapRGB(window_surface->format, x * random(0, 255), x * y * random(0, 255), random(0, 255));
			}
		}

		CopyMemory( window_buffer, back, (width * height * sizeof(uint32_t)) );

		// unlock surface buffer
		SDL_UnlockSurface(window_surface);

		SDL_UpdateWindowSurface(window);
		window_buffer = (uint32_t*)(window_surface->pixels);
		std::swap(front, back);

	}

	delete[] front;
	delete[] back;

	// free sdl stuff
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Shuts down all SDL subsystems 
	SDL_Quit();

	return 0;
}
// end : main function

uint8_t random(uint8_t min , uint8_t max) {
	std::srand(time(0));
	
	return (uint8_t)(std::rand() - max + min);

}

uint32_t random32(uint32_t min, uint32_t max) {
	std::srand(time(0));

	return (uint32_t)(std::rand() - max + min);

}