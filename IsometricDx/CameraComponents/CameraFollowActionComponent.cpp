#include "CameraFollowActionComponent.h"

#include <iostream>
#include <math.h>
#include "../Globals.h"
#include "../GameObject.h"

CameraFollowActionComponent::CameraFollowActionComponent(GameObject* camera, GameObject* player)
{
	this->host = camera;
	this->target = player;
}


CameraFollowActionComponent::~CameraFollowActionComponent()
{
}

void CameraFollowActionComponent::Update()
{
	StrictFollow();
}

void CameraFollowActionComponent::HysteresisFollow()
{
	int border_x = (int) 0.2 * SCREEN_WIDTH;
	int border_y = (int) 0.2 * SCREEN_HEIGHT;

	// NOT SMOOTH AT ALL, NEEDS REWORK

	int target_screen_x, target_screen_y;
	GameToScreen(target->x, target->y, target_screen_x, target_screen_y);
	target_screen_x += ORIGIN;

	int cam_x = host->x;
	int cam_y = host->y;

	if (target_screen_x - cam_x < border_x)
	{
		host->x -= border_x - (target_screen_x - cam_x);
	}
	else if (cam_x + SCREEN_WIDTH - (target_screen_x + TILE_SIZE) < border_x)
	{
		host->x += border_x - (cam_x + SCREEN_WIDTH - (target_screen_x + TILE_SIZE));
	}
	if (target_screen_y - cam_y < border_y)
	{
		host->y -= border_y - (target_screen_y - cam_y);
	}
	else if (cam_y + SCREEN_HEIGHT - (target_screen_y + TILE_SIZE) < border_y)
	{
		host->y += border_y - (cam_y + SCREEN_HEIGHT - (target_screen_y + TILE_SIZE));
	}
}

void CameraFollowActionComponent::StrictFollow()
{
	int target_screen_x, target_screen_y;
	GameToScreen(target->x, target->y, target_screen_x, target_screen_y);
	target_screen_x += ORIGIN;

	host->x = target_screen_x - SCREEN_WIDTH/2 + TILE_SIZE/2;
	host->y = target_screen_y - SCREEN_HEIGHT/2 + TILE_SIZE / 2;
}
