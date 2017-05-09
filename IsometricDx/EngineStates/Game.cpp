#include "Game.h"

#include "../GameStates/GameIntro.h"
#include "../Engine.h"
#include <SDL.h>
#include <iostream>

Game::Game(Engine* engine, SDL_Renderer* renderer)
{
	gamestate = new GameIntro(this, renderer);
	this->engine = engine;
}


Game::~Game()
{
	delete gamestate;
	std::cout << "Deleting Game..." << std::endl;
}

void Game::Update()
{
	gamestate->Update();
}

void Game::Render(SDL_Renderer * renderer)
{
	gamestate->Render(renderer);
}
