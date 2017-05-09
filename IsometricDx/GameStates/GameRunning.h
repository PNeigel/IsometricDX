#pragma once
#include "GameState.h"
#include <SDL.h>

class Level;
class Game;

class GameRunning : public GameState
{
public:
	GameRunning(Game* game, SDL_Renderer* renderer);
	~GameRunning();

	void Update();
	void Render(SDL_Renderer* renderer);

	Level* level = nullptr;
	Game* game = nullptr;
};

