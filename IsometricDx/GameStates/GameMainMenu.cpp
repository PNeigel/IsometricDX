#include "GameMainMenu.h"

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "..\EngineStates\Game.h"
#include "GameRunning.h"
#include "..\Engine.h"

GameMainMenu::GameMainMenu(Game* game, SDL_Renderer* renderer)
{
	this->game = game;
	this->renderer = renderer;
	LoadTextures();
}


GameMainMenu::~GameMainMenu()
{
	SDL_DestroyTexture(play_texture);
	SDL_DestroyTexture(exit_texture);
	std::cout << "Deleting MainMenu" << std::endl;
}

void GameMainMenu::Update()
{
	if (selection_cooldown > 0) selection_cooldown -= 1;
	HandleInput();
}

void GameMainMenu::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool up = state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
	bool down = state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
	bool enter = state[SDL_SCANCODE_RETURN];

	if (up && selection_cooldown == 0)
	{
		selection -= 1;
		selection_cooldown = 10;
	}
	else if (down && selection_cooldown == 0)
	{
		selection += 1;
		selection_cooldown = 10;
	}

	if (selection < 0) selection = PLAY;
	if (selection > 1) selection = EXIT;

	if (enter)
	{
		if (selection == PLAY) {
			game->gamestate = new GameRunning(game, renderer);
			delete this;
		}
		if (selection == EXIT)
		{
			game->engine->Close();
		}
	}
}

void GameMainMenu::Render(SDL_Renderer * renderer)
{
	SDL_RenderClear(renderer);
	if (selection == PLAY) SDL_RenderCopy(renderer, play_texture, nullptr, nullptr);
	if (selection == EXIT) SDL_RenderCopy(renderer, exit_texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void GameMainMenu::LoadTextures()
{
	std::string path = "Assets/Sprites/MenuPlay.png";
	SDL_Surface* temp_surface = temp_surface = IMG_Load(path.c_str());
	play_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	SDL_SetTextureBlendMode(play_texture, SDL_BLENDMODE_BLEND);

	path = "Assets/Sprites/MenuExit.png";
	temp_surface = temp_surface = IMG_Load(path.c_str());
	exit_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
}
