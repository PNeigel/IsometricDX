#pragma once

#include <SDL.h>

class EngineState;

class Engine {
public:
	Engine();
	~Engine();

	EngineState* engine_state;

	SDL_Renderer* renderer = nullptr;

	// Start the engine
	void Go();

	void Close();

	int fps_avg = 0;
	int ticks_avg = 0;
	int frames = 0;
	int ticks = 0;
	int elapsed;
	int cumulative_elapsed;

	SDL_Event e;

private:

	SDL_Window* window = nullptr;
	SDL_Surface* temp_surface = nullptr;
	SDL_Texture* temp_texture = nullptr;
	SDL_Rect rect, srcrect;

	bool Init();

	void MainLoop();

};