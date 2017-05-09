#include "SkeletonGraphicsComponent.h"


SkeletonGraphicsComponent::SkeletonGraphicsComponent(GameObject* skeleton, SDL_Texture* sprite_sheet, int sprite_no)
{
	this->host = skeleton;
	this->sprite_sheet = sprite_sheet;
	this->sprite_no = sprite_no;
}


SkeletonGraphicsComponent::~SkeletonGraphicsComponent()
{
}
