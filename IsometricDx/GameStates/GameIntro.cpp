#include "GameIntro.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#include "..\EngineStates\Game.h"
#include "GameMainMenu.h"
#include "..\Globals.h"

GameIntro::GameIntro(Game* game, SDL_Renderer* renderer)
{
	this->game = game;
	this->renderer = renderer;
	LoadTexture("Assets/Sprites/Intro.png");
}


GameIntro::~GameIntro()
{
	SDL_DestroyTexture(intro_texture);
	std::cout << "Deleting Intro" << std::endl;
}

void GameIntro::Update()
{
	if (duration > 0)
	{
		duration -= 1;
		Uint8 alpha = (Uint8) (duration*255 / 180.0);
		SDL_SetTextureAlphaMod(intro_texture, alpha);

	}
	else
	{
		game->gamestate = new GameMainMenu(game, renderer);
		delete this;
	}
}

void GameIntro::Render(SDL_Renderer * renderer)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, intro_texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void GameIntro::LoadTexture(std::string path)
{
	SDL_Surface* temp_surface = temp_surface = IMG_Load(path.c_str());
	intro_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	SDL_SetTextureBlendMode(intro_texture, SDL_BLENDMODE_BLEND);
}
