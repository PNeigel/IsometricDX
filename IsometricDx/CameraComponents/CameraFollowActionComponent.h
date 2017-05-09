#pragma once
#include "../Components/ActionComponent.h"

class GameObject;

class CameraFollowActionComponent :
	public ActionComponent
{
public:
	CameraFollowActionComponent(GameObject* camera, GameObject* player);
	~CameraFollowActionComponent();

	void Update();

	void HysteresisFollow();
	void StrictFollow();
	void Run() {}

	GameObject* target;
};

