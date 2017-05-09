#pragma once

#include <SDL.h>

class GameObject;

class GraphicsComponent
{
public:
	~GraphicsComponent();

	virtual void Render(SDL_Renderer* renderer, GameObject* camera);

	GameObject* host;
	SDL_Texture* sprite_sheet;
	int sprite_no;
};