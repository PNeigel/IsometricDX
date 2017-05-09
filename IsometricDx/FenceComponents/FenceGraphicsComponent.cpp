#include "FenceGraphicsComponent.h"

#include "..\GameObject.h"

FenceGraphicsComponent::FenceGraphicsComponent(GameObject* fence, SDL_Texture* sprite_sheet, int sprite_no)
{
	this->host = fence;
	this->sprite_sheet = sprite_sheet;
	this->sprite_no = sprite_no;
}


FenceGraphicsComponent::~FenceGraphicsComponent()
{
}
