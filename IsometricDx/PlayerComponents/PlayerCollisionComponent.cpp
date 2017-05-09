#include "PlayerCollisionComponent.h"

#include <cmath>
#include <iostream>

#include "..\GameObject.h"
#include "..\Levels\Level.h"

PlayerCollisionComponent::PlayerCollisionComponent(GameObject* player, Level* level)
{
	this->host = player;
	this->level = level;
	box_w = 64;
	box_h = 64;
}


PlayerCollisionComponent::~PlayerCollisionComponent()
{
}

void PlayerCollisionComponent::ResolveCollisionStatic(float x_corr, float y_corr)
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

void PlayerCollisionComponent::IterateObjects(std::vector<GameObject*> obj_list)
{
	int i;
	float x_corr, y_corr;
	for (i = 0; i < obj_list.size(); i++)
	{
		if (CheckCollision(obj_list[i], x_corr, y_corr))
		{
			ResolveCollisionStatic(x_corr, y_corr);
		}
	}
}

void PlayerCollisionComponent::Update()
{
	UpdatePosition();
	IterateObjects(level->statics);
}
