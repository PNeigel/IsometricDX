#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\CollisionComponent.h"

#include <vector>

class Level;

class ProjectileCollisionComponent :
	public CollisionComponent
{
public:
	ProjectileCollisionComponent(GameObject* projectile, Level* level);
	~ProjectileCollisionComponent();

	void Update();
	void IterateObjects(std::vector<GameObject*> obj_list);
	void ResolveCollision(GameObject* target);

	Level* level;
};

