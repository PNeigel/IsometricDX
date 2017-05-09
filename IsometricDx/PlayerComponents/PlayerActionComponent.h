#pragma once
#include "../Components/ActionComponent.h"

#include <SDL.h>

class GameObject;
class Level;

class PlayerActionComponent :
	public ActionComponent
{
public:
	PlayerActionComponent(GameObject* player, Level* level);
	~PlayerActionComponent();

	void Update();
	void SetOrientation(float xor, float yor);
	void SetVelocity(bool run);
	void SetShoot(bool shoot);
	void Run();
	void Shoot();
	void TimerUpdate();

	int shoot_cooldown = 0;
	bool shoot_request = false;
	int timer = SDL_GetTicks();

	Level* level;
};

