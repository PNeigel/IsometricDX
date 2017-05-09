#include "GameRunning.h"

#include <SDL.h>
#include <iostream>

#include "../Levels/Level.h"
#include "../EngineStates/Game.h"


GameRunning::GameRunning(Game* game, SDL_Renderer* renderer)
{
	level = new Level(game, renderer);
	this->game = game;
}


GameRunning::~GameRunning()
{
	delete level;
	std::cout << "Deleting GameRunning state..." << std::endl;
}

void GameRunning::Update()
{
	level->UpdateIngameState();
}

void GameRunning::Render(SDL_Renderer * renderer)
{
	level->RenderIngameState();
}
