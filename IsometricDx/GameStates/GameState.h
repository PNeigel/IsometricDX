#pragma once

#include <SDL.h>

class GameState
	// Interface for Intro, MainMenu, GameRunning
{
public:
	GameState();
	virtual ~GameState();

	virtual void Update() {}
	virtual void Render(SDL_Renderer* renderer) {};
};

