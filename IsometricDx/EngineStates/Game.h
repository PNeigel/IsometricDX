#pragma once
#include "EngineState.h"
#include <SDL.h>
class GameState;
class Engine;

class Game : public EngineState
{
public:
	Game(Engine* engine, SDL_Renderer* renderer);
	~Game();

	void Update();
	void Render(SDL_Renderer* renderer);
	
	GameState* gamestate;
	Engine* engine;

};

