#pragma once

#include <SDL.h>

class GameObject;

class InputComponent
{
public:
	virtual ~InputComponent() {}

	virtual void Update() = 0;

	GameObject* host;
};