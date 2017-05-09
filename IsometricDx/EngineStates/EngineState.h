#pragma once
#include <SDL.h>

class EngineState
	// Interface for the states GAME and EDITOR
{
public:
	EngineState() {}
	virtual ~EngineState() {}

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) {}

private:


};