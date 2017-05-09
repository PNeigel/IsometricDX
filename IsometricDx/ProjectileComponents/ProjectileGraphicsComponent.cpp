#include "ProjectileGraphicsComponent.h"


ProjectileGraphicsComponent::ProjectileGraphicsComponent(GameObject* projectile, SDL_Texture* sprite_sheet, int sprite_no)
{
	this->host = projectile;
	this->sprite_sheet = sprite_sheet;
	this->sprite_no = sprite_no;
}


ProjectileGraphicsComponent::~ProjectileGraphicsComponent()
{
}
