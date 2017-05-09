#include "../PlayerComponents/PlayerGraphicsComponent.h"

#include <SDL.h>
#include <iostream>

#include "../Globals.h"
#include "../GameObject.h"

PlayerGraphicsComponent::PlayerGraphicsComponent(GameObject* player, SDL_Texture* sprite_sheet, int sprite_no)
{
	this->host = player;
	this->sprite_sheet = sprite_sheet;
	this->sprite_no = sprite_no;
}


PlayerGraphicsComponent::~PlayerGraphicsComponent()
{
	std::cout << "Deleting Player Graphics" << std::endl;
}
