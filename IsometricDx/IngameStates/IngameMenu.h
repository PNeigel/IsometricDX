#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\IngameStates\IngameState.h"

#include <SDL.h>

class Level;

class IngameMenu :
	public IngameState
{
public:
	enum {
		RESUME,
		EXIT
	};
	IngameMenu(Level* level);
	~IngameMenu();

	void Render();
	void RenderMenu();
	void Update();
	void HandleInput();

	void LoadTextures();

	int menu_state = RESUME;

	SDL_Texture* menu_1 = nullptr;
	SDL_Texture* menu_2 = nullptr;
};

