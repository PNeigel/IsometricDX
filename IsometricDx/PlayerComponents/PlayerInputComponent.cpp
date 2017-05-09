#include "../PlayerComponents/PlayerInputComponent.h"

#include <SDL.h>
#include <iostream>
#include "../Globals.h"

#include "../GameObject.h"
#include "../Components/ActionComponent.h"

PlayerInputComponent::PlayerInputComponent(GameObject* player)
{
	this->host = player;
}


PlayerInputComponent::~PlayerInputComponent()
{
}

void PlayerInputComponent::Update()
{
	HandleInput();
}

void PlayerInputComponent::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool up = state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
	bool down = state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
	bool left = state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];
	bool right = state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];

	float x_orientation = host->orientation[0];
	float y_orientation = host->orientation[1];

	bool run = HandleOrientationByArrowKeys(up, down, left, right, x_orientation, y_orientation);
	bool shoot = state[SDL_SCANCODE_SPACE];

	if (host->action_component->kickback == 0) host->action_component->SetOrientation(x_orientation, y_orientation);
	host->action_component->SetVelocity(run);
	host->action_component->SetShoot(shoot);

}

const static float invsqrt2 = 1 / sqrt(2);
bool PlayerInputComponent::HandleOrientationByArrowKeys(bool up, bool down, bool left, bool right, float& x, float& y)
{
	bool pressed = false;
	if (up && left)
	{
		x = -1;
		y = 0;
		pressed = true;
	}
	else if (up && right)
	{
		x = 0;
		y = -1;
		pressed = true;
	}
	else if (down && right)
	{
		x = +1;
		y = 0;
		pressed = true;
	}
	else if (down && left)
	{
		x = 0;
		y = +1;
		pressed = true;
	}
	else if (up)
	{
		x = -invsqrt2;
		y = -invsqrt2;
		pressed = true;
	}
	else if (down)
	{
		x = invsqrt2;
		y = invsqrt2;
		pressed = true;
	}
	else if (left)
	{
		x = -invsqrt2;
		y = invsqrt2;
		pressed = true;
	}
	else if (right)
	{
		x = invsqrt2;
		y = -invsqrt2;
		pressed = true;
	}

	return pressed;
}
