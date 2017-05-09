#pragma once

class GameObject;

class ActionComponent
{
public:
	virtual ~ActionComponent() {}

	virtual void Update() {}
	virtual void Run() {}
	virtual void SetOrientation(float xor, float yor) {}
	virtual void SetVelocity(bool run) {}
	virtual void SetShoot(bool shoot) {}
	virtual void Shoot() {}
	virtual void TimerUpdate() {}
	virtual void ApplyDamage(GameObject* target, int damage) {}
	virtual void Destroy() {}

	GameObject* host;

	bool destroy_order = false;
	int kickback = 0; // Number of frames of kickback
};