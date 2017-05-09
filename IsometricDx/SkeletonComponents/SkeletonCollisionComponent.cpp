#include "SkeletonCollisionComponent.h"

#include <math.h>
#include "..\GameObject.h"
#include "..\Components\ActionComponent.h"
#include "..\Components\StatsComponent.h"
#include "..\Levels\Level.h"

SkeletonCollisionComponent::SkeletonCollisionComponent(GameObject* skeleton, Level* level)
{
	this->host = skeleton;
	this->level = level;
	box_w = 64;
	box_h = 64;
}


SkeletonCollisionComponent::~SkeletonCollisionComponent()
{

}

void SkeletonCollisionComponent::ResolveCollisionPlayer(float x_corr, float y_corr)
{
	host->action_component->ApplyDamage(level->player, host->stats_component->damage);
	level->player->action_component->kickback = 10;
	float absolute = sqrt(pow(x_corr, 2) + pow(y_corr, 2));
	level->player->action_component->SetOrientation(x_corr/absolute, y_corr/absolute);
}

void SkeletonCollisionComponent::ResolveCollisionBlock(float x_corr, float y_corr)
{
	if (abs(x_corr) <= abs(y_corr))
	{
		host->x += x_corr;
	}
	else
	{
		host->y += y_corr;
	}
}

void SkeletonCollisionComponent::Update()
{
	float x_corr, y_corr;
	UpdatePosition();
	if (CheckCollision(level->player, x_corr, y_corr))
	{
		ResolveCollisionPlayer(x_corr, y_corr);
	}
	IterateObjects(level->statics);
	IterateObjects(level->enemies);
}

void SkeletonCollisionComponent::IterateObjects(std::vector<GameObject*> obj_list)
{
	int i;
	float x_corr, y_corr;
	for (i = 0; i < obj_list.size(); i++)
	{
		if (CheckCollision(obj_list[i], x_corr, y_corr) && host != obj_list[i])
		{
			ResolveCollisionBlock(x_corr, y_corr);
		}
	}
}
