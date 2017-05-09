#pragma once
#include "../Components/GraphicsComponent.h"

#include <SDL.h>

class GameObject;

class ProjectileGraphicsComponent :
	public GraphicsComponent
{
public:
	ProjectileGraphicsComponent(GameObject* projectile, SDL_Texture* sprite_sheet, int sprite_no);
	~ProjectileGraphicsComponent();
};

