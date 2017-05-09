#include "CollisionComponent.h"

#include <iostream>
#include "../GameObject.h"
#include "../Globals.h"

bool CollisionComponent::CheckCollision(GameObject* target, float& x_corr, float& y_corr)
{
	bool collision = false;

	if (target->collision_component != nullptr)
	{
		float tx = target->collision_component->box_x;
		float ty = target->collision_component->box_y;
		float tw = target->collision_component->box_w;
		float th = target->collision_component->box_h;

		bool x_overlap = (box_x + box_w > tx) && (box_x < tx + tw);
		bool y_overlap = (box_y + box_h > ty) && (box_y < ty + th);

		collision = x_overlap && y_overlap;

		float left = box_x + box_w - tx;
		float right = tx + tw - box_x;
		float up = box_y + box_h - ty;
		float down = ty + th - box_y;
		
		if (collision)
		{
			if (left <= right) x_corr = -left;
			else x_corr = right;
			if (up <= down) y_corr = -up;
			else y_corr = down;
		}
		else
		{
			x_corr = 0;
			y_corr = 0;
		}
	}
	return collision;
}

void CollisionComponent::UpdatePosition()
{
	box_x = host->x;
	box_y = host->y;
}

void CollisionComponent::ResolveCollision(GameObject * target)
{
}
