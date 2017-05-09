#include "PlayerStatsComponent.h"

#include "../GameObject.h"

PlayerStatsComponent::PlayerStatsComponent(GameObject* player)
{
	this->host = player;
	this->max_hp = 1000;
	this->current_hp = max_hp;
}


PlayerStatsComponent::~PlayerStatsComponent()
{
}
