#include "ProjectileActionComponent.h"

#include <iostream>

#include "../GameObject.h"
#include "../Levels/Level.h"
#include "../Components/StatsComponent.h"


ProjectileActionComponent::ProjectileActionComponent(GameObject* projectile, Level* level)
{
	this->host = projectile;
	this->level = level;
}


ProjectileActionComponent::~ProjectileActionComponent()
{
}

void ProjectileActionComponent::Update()
{
	Move();
}

void ProjectileActionComponent::Move()
{
	host->x += host->orientation[0] * host->velocity;
	host->y += host->orientation[1] * host->velocity;
	max_distance -= host->velocity;
	if (max_distance <= 0) host->action_component->destroy_order = true;
}

void ProjectileActionComponent::ApplyDamage(GameObject * target, int damage)
{
	target->stats_component->current_hp -= damage;
}
