#include "CameraKeyInputComponent.h"

#include <math.h>
#include <iostream>
#include <SDL.h>

#include "../GameObject.h"


CameraKeyInputComponent::CameraKeyInputComponent(GameObject* camera)
{
	this->host = camera;
}


CameraKeyInputComponent::~CameraKeyInputComponent()
{
	std::cout << "Deleting CameraKeyInputComponent..." << std::endl;
}

void CameraKeyInputComponent::Update(SDL_Event* e)
{
	HandleInput();
}

void CameraKeyInputComponent::HandleInput()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	bool up = state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
	bool down = state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];
	bool left = state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];
	bool right = state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];

	bool pressed = HandleOrientationByArrowKeys(up, down, left, right, host->orientation[0], host->orientation[1]);

	if (!pressed) host->velocity = 0;
	else host->velocity = CAMERA_VELOCITY;
	
}

const static float invsqrt2 = 1/sqrt(2);
bool CameraKeyInputComponent::HandleOrientationByArrowKeys(bool up, bool down, bool left, bool right, float& x, float& y)
{
	bool pressed = false;
	if (up && left)
	{
		x = -invsqrt2;
		y = -invsqrt2;
		pressed = true;
	}
	else if (up && right)
	{
		x = invsqrt2;
		y = -invsqrt2;
		pressed = true;
	}
	else if (down && right)
	{
		x = invsqrt2;
		y = invsqrt2;
		pressed = true;
	}
	else if (down && left)
	{
		x = -invsqrt2;
		y = invsqrt2;
		pressed = true;
	}
	else if (up)
	{
		x = 0;
		y = -1;
		pressed = true;
	}
	else if (down)
	{
		x = 0;
		y = 1;
		pressed = true;
	}
	else if (left)
	{
		x = -1;
		y = 0;
		pressed = true;
	}
	else if (right)
	{
		x = 1;
		y = 0;
		pressed = true;
	}

	return pressed;
}
