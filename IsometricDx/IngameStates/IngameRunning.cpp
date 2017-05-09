#include "IngameRunning.h"

#include <SDL.h>
#include "../Globals.h"

#include "../Levels/Level.h"
#include "../GameObject.h"
#include "../Components/StatsComponent.h"

IngameRunning::IngameRunning(Level* level)
{
	this->level = level;
}


IngameRunning::~IngameRunning()
{
}

void IngameRunning::Render()
{
	SDL_RenderClear(level->renderer);
	RenderLevel();
	RenderGUI();
	SDL_RenderPresent(level->renderer);
}

void IngameRunning::Update()
{
	if (level->menu_cd > 0) level->menu_cd -= 1;
	HandleInput();
	level->UpdateAssets();
}

void IngameRunning::HandleInput()
{
	// Handles Input to change from one ingamestate to another, e.g. from running to inventory or menu
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool esc = state[SDL_SCANCODE_ESCAPE];

	if (esc && level->menu_cd == 0)
	{
		level->ingamestate = level->menustate;
		level->menu_cd = 10;
	}
}

void IngameRunning::RenderGUI()
{
	for (auto obj : level->enemies)
	{
		RenderEnemyHP(obj);
	}
	RenderPlayerHP();
}

void IngameRunning::RenderEnemyHP(GameObject* enemy)
{
	SDL_Rect srcrect, dstrect;
	int x, y;

	GameToScreen(enemy->x, enemy->y, x, y);

	// Hitpoints Background

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 256;
	srcrect.h = 70;

	dstrect.x = x - level->camera->x + ORIGIN;
	dstrect.y = y - level->camera->y - TILE_SIZE / 2 - 35;
	dstrect.w = 128;
	dstrect.h = 35;

	SDL_RenderCopy(level->renderer, level->sprite_sheets[3], &srcrect, &dstrect);

	// Hitpoints Foreground

	float frac = enemy->stats_component->current_hp / (float) enemy->stats_component->max_hp;

	srcrect.x = 0;
	srcrect.y = 71;
	srcrect.w = 225 * frac;
	srcrect.h = 50;

	dstrect.x = x - level->camera->x + ORIGIN + 8;
	dstrect.y = y - level->camera->y - TILE_SIZE / 2 - 35 + 5;
	dstrect.w = 112 * frac;
	dstrect.h = 25;

	SDL_RenderCopy(level->renderer, level->sprite_sheets[3], &srcrect, &dstrect);
}

void IngameRunning::RenderPlayerHP()
{
	SDL_Rect srcrect, dstrect;
	int x, y;

	GameToScreen(level->player->x, level->player->y, x, y);

	// Hitpoints Background

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 256;
	srcrect.h = 70;

	dstrect.x = 5;
	dstrect.y = 5;
	dstrect.w = SCREEN_WIDTH/3;//128;
	dstrect.h = 35;

	SDL_RenderCopy(level->renderer, level->sprite_sheets[3], &srcrect, &dstrect);

	// Hitpoints Foreground

	float frac = level->player->stats_component->current_hp / (float) level->player->stats_component->max_hp;

	srcrect.x = 0;
	srcrect.y = 71;
	srcrect.w = 225 * frac;
	srcrect.h = 50;

	dstrect.x = 5 + (256-225)/(float) (256*2) * SCREEN_WIDTH / 3;
	dstrect.y = 5 + 5;
	dstrect.w = frac * 225 / (float) 256 * SCREEN_WIDTH / 3;//112 * frac;
	dstrect.h = 25;

	SDL_RenderCopy(level->renderer, level->sprite_sheets[3], &srcrect, &dstrect);
}

void IngameRunning::RenderLevel()
{
	level->RenderAssets();
}
