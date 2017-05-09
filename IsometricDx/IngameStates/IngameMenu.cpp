#include "IngameMenu.h"

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "..\Levels\Level.h"
#include "..\Globals.h"

IngameMenu::IngameMenu(Level* level)
{
	this->level = level;
	LoadTextures();
}


IngameMenu::~IngameMenu()
{
	SDL_DestroyTexture(menu_1);
	SDL_DestroyTexture(menu_2);
}

void IngameMenu::Render()
{
	SDL_RenderClear(level->renderer);
	level->RenderAssets();
	RenderMenu();
	SDL_RenderPresent(level->renderer);
}

void IngameMenu::RenderMenu()
{
	SDL_Rect dstrect;

	dstrect.x = SCREEN_WIDTH / 4;
	dstrect.y = SCREEN_HEIGHT / 4;
	dstrect.w = SCREEN_WIDTH / 2;
	dstrect.h = SCREEN_HEIGHT / 2;

	if (menu_state == RESUME) SDL_RenderCopy(level->renderer, menu_1, nullptr, &dstrect);
	if (menu_state == EXIT) SDL_RenderCopy(level->renderer, menu_2, nullptr, &dstrect);
}

void IngameMenu::Update()
{
	if (level->menu_cd > 0) level->menu_cd -= 1;
	HandleInput();
}

void IngameMenu::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool esc = state[SDL_SCANCODE_ESCAPE];
	bool up = state[SDL_SCANCODE_UP];
	bool down = state[SDL_SCANCODE_DOWN];
	bool enter = state[SDL_SCANCODE_RETURN];

	if (esc && level->menu_cd == 0)
	{
		level->ingamestate = level->runningstate;
		level->menu_cd = 10;
	}
	if (up && level->menu_cd == 0)
	{
		menu_state -= 1;
		level->menu_cd = 10;
	}
	if (down && level->menu_cd == 0)
	{
		menu_state += 1;
		level->menu_cd = 10;
	}
	if (menu_state < 0) menu_state = RESUME;
	if (menu_state > EXIT) menu_state = EXIT;
	if (enter && level->menu_cd == 0)
	{
		if (menu_state == RESUME) level->ingamestate = level->runningstate;
		if (menu_state == EXIT) level->ReturnToMainMenu();
	}

}

void IngameMenu::LoadTextures()
{
	std::string path = "Assets/Sprites/IngameMenu_1.png";
	SDL_Surface* temp_surface = IMG_Load(path.c_str());
	menu_1 = SDL_CreateTextureFromSurface(level->renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	path = "Assets/Sprites/IngameMenu_2.png";
	temp_surface = IMG_Load(path.c_str());
	menu_2 = SDL_CreateTextureFromSurface(level->renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
}
