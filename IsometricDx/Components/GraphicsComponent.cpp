#include "GraphicsComponent.h"


#include "../Globals.h"
#include "../GameObject.h"

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::Render(SDL_Renderer * renderer, GameObject * camera)
{
	SDL_Rect srcrect, dstrect;
	int x, y;

	GameToScreen(host->x,host->y, x, y);

	srcrect.x = (sprite_no % SHEET_WIDTH) * TILE_SIZE;
	srcrect.y = (sprite_no / SHEET_WIDTH) * TILE_SIZE;
	srcrect.w = TILE_SIZE;
	srcrect.h = TILE_SIZE;

	dstrect.x = x - camera->x + ORIGIN;
	dstrect.y = y - camera->y - TILE_SIZE / 2;
	dstrect.w = TILE_SIZE;
	dstrect.h = TILE_SIZE;

	SDL_RenderCopy(renderer, sprite_sheet, &srcrect, &dstrect);
}
