#include "SkeletonActionComponent.h"

#include <math.h>

#include "..\GameObject.h"
#include "..\Levels\Level.h"
#include "..\Components\StatsComponent.h"

SkeletonActionComponent::SkeletonActionComponent(GameObject* skeleton, Level* level)
{
	this->host = skeleton;
	this->level = level;
}


SkeletonActionComponent::~SkeletonActionComponent()
{
}

void SkeletonActionComponent::Update()
{
	Move();
}

void SkeletonActionComponent::Move()
{
	host->orientation[0] = level->player->x - host->x;
	host->orientation[1] = level->player->y - host->y;

	float dist = sqrt(pow(host->orientation[0], 2) + pow(host->orientation[1], 2));

	if (dist < 500)
	{
		host->orientation[0] /= dist;
		host->orientation[1] /= dist;

		host->x += host->orientation[0] * host->velocity;
		host->y += host->orientation[1] * host->velocity;
	}
	if (host->x < 0) host->x = 0;
	if (host->y < 0) host->y = 0;

}

void SkeletonActionComponent::ApplyDamage(GameObject * target, int damage)
{
	if (target->action_component->kickback == 0) target->stats_component->current_hp -= damage;
}