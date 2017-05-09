#pragma once
#include "../Components/InputComponent.h"

class GameObject;

class CameraKeyInputComponent :
	public InputComponent
{
public:
	CameraKeyInputComponent(GameObject* camera);
	~CameraKeyInputComponent();

	void Update(SDL_Event* e);
	void HandleInput();

	bool HandleOrientationByArrowKeys(bool up, bool down, bool left, bool right, float& x, float& y);

	const static int CAMERA_VELOCITY = 10;
};

