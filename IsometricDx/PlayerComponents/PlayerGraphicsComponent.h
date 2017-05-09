#pragma once
#include "../Components/GraphicsComponent.h"

#include <SDL.h>

class GameObject;

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
	PlayerGraphicsComponent(GameObject* player, SDL_Texture* sprite_sheet, int sprite_no);
	~PlayerGraphicsComponent();
};

