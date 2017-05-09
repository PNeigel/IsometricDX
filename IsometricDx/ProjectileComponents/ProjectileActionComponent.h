#pragma once
#include "../Components/ActionComponent.h"

class GameObject;
class Level;

class ProjectileActionComponent :
	public ActionComponent
{
public:
	ProjectileActionComponent(GameObject* projectile, Level* level);
	~ProjectileActionComponent();

	void Update();

	void Move();
	void ApplyDamage(GameObject* target, int damage);

	float max_distance = 1000;

	Level* level;
};

