#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\GameStates\GameState.h"

#include <string>
#include <SDL.h>

class Game;

class GameIntro :
	public GameState
{
public:
	GameIntro(Game* game, SDL_Renderer* renderer);
	~GameIntro();

	void Update();
	void Render(SDL_Renderer* renderer);
	void LoadTexture(std::string path);

	SDL_Texture* intro_texture = nullptr;

	Game* game;
	SDL_Renderer* renderer;
	int duration = 180;
};

