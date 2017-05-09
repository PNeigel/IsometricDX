#include "ProjectileCollisionComponent.h"

#include <iostream>
#include <vector>

#include "../GameObject.h"
#include "../Levels\Level.h"
#include "../Components\ActionComponent.h"


ProjectileCollisionComponent::ProjectileCollisionComponent(GameObject* projectile, Level* level)
{
	this->host = projectile;
	this->level = level;
	box_w = 64;
	box_h = 64;
}


ProjectileCollisionComponent::~ProjectileCollisionComponent()
{
}

void ProjectileCollisionComponent::Update()
{
	UpdatePosition();
	IterateObjects(level->statics);
	IterateObjects(level->enemies);
}

void ProjectileCollisionComponent::ResolveCollision(GameObject * target)
{
	if (target->action_component != nullptr) host->action_component->ApplyDamage(target, 100);
	host->action_component->destroy_order = true;
}

void ProjectileCollisionComponent::IterateObjects(std::vector<GameObject*> obj_list)
{
	int i;
	bool collision = false;
	float x_corr, y_corr;
	for (i = 0; i < obj_list.size(); i++)
	{
		if (CheckCollision(obj_list[i], x_corr, y_corr))
		{
			collision = true;
			break;
		}
	}
	if (collision) ResolveCollision(obj_list[i]);
}
