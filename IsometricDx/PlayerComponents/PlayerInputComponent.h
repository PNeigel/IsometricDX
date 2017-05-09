#pragma once
#include "../Components/InputComponent.h"

#include <SDL.h>

class GameObject;

class PlayerInputComponent :
	public InputComponent
{
public:
	PlayerInputComponent(GameObject* player);
	~PlayerInputComponent();

	void Update();
	void HandleInput();

	bool HandleOrientationByArrowKeys(bool up, bool down, bool left, bool right, float & x, float & y);
};

