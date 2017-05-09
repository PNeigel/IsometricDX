#include "FenceCollisionComponent.h"

#include <iostream>

#include "..\GameObject.h"

FenceCollisionComponent::FenceCollisionComponent(GameObject* fence, int sprite_no)
{
	this->host = fence;
	SetDims(sprite_no);
}


FenceCollisionComponent::~FenceCollisionComponent()
{
}

void FenceCollisionComponent::SetDims(int sprite_no)
{
	if (sprite_no == 40 || sprite_no == 41 || sprite_no == 42 || sprite_no == 43)
		// Corners
	{
		box_w = 40;
		box_h = 40;
		box_x = host->x + 12;
		box_y = host->y + 12;
	}
	else if (sprite_no == 44 || sprite_no == 45 || sprite_no == 46 || sprite_no == 47)
		// Single Post
	{
		box_w = 20;
		box_h = 20;
		box_x = host->x + 22;
		box_y = host->y + 22;
	}
	else if (sprite_no == 48 || sprite_no == 49 || sprite_no == 52 || sprite_no == 53)
		// Horizontal
	{
		box_w = 64;
		box_h = 20;
		box_x = host->x;
		box_y = host->y + 22;
	}
	else if (sprite_no == 50 || sprite_no == 51 || sprite_no == 54 || sprite_no == 55)
		// Vertical
	{
		box_w = 20;
		box_h = 64;
		box_x = host->x + 22;
		box_y = host->y;
	}
}
