#include "Engine.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Globals.h"
#include "./EngineStates/Game.h"
#include <chrono>
#include <iostream>

Engine::Engine() {

}

Engine::~Engine() {
	std::cout << "Deleting engine..." << std::endl;
}

bool Engine::Init() {

	// Initialization flag
	bool success = true;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {

		// Create Window
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				SDL_SetRenderDrawColor(renderer, 180, 180, 250, 200);

				if (renderer == NULL) {
					printf("Renderer could not be initialized. SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				if (TTF_Init() == -1)
				{
					printf("TTF_Init: %s\n", TTF_GetError());
					success = false;
				}

			}
		}
	}

	engine_state = new Game(this, renderer);

	return success;
}

void Engine::Close() {

	std::cout << "Stopping engine..." << std::endl;
	//Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	delete engine_state;
	engine_state = nullptr;
	
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}


void Engine::MainLoop() {

	int MS_PER_TICK = 16;

	using namespace std::chrono;
	//milliseconds previous = duration_cast<milliseconds>(system_clock::now().time_since_epoch() );
	//milliseconds current;

	int previous = SDL_GetTicks();
	int current = SDL_GetTicks();
	int lag = 0;
	cumulative_elapsed = 0;

	while (window != NULL) {
		//current = duration_cast<milliseconds>(system_clock::now().time_since_epoch() );
		//elapsed = current.count() - previous.count();
		elapsed = current - previous;
		previous = current;
		cumulative_elapsed += elapsed;

		if (cumulative_elapsed > 3000)
		{
			cumulative_elapsed -= 3000;
			fps_avg = frames / 3;
			ticks_avg = ticks / 3;
			frames = 0;
			ticks = 0;
		}
		lag += elapsed;
		while (lag >= MS_PER_TICK) {
			lag -= MS_PER_TICK;
			ticks++;
			engine_state->Update();
			if (engine_state != nullptr)
			{
				engine_state->Render(renderer);
			}
			frames++;
		}

		// Poll SDL Events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					Close();
					break;

				default:
					break;
				}
			}
			else if (e.type == SDL_QUIT) {
				Close();
				printf("\nGame was X-ed out and quit\n\n");
			}
		}
		current = SDL_GetTicks();
	}
}


void Engine::Go() {
	if (!Init()) printf("Could not initialize Engine!\n");

	MainLoop();
}