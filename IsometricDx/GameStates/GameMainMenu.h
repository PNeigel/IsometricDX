#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\GameStates\GameState.h"

#include <SDL.h>



class Game;

class GameMainMenu :
	public GameState
{
public:
	enum {
		PLAY,
		EXIT
	};
	GameMainMenu(Game* game, SDL_Renderer* renderer);
	~GameMainMenu();

	void Update();
	void HandleInput();
	void Render(SDL_Renderer* renderer);
	void LoadTextures();

	int selection = PLAY;

	int selection_cooldown = 0;

	int fadeout = 120;

	SDL_Texture* play_texture = nullptr;
	SDL_Texture* exit_texture = nullptr;

	Game* game;
	SDL_Renderer* renderer;
};

