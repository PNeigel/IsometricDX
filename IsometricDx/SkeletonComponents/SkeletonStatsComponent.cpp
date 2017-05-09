#include "SkeletonStatsComponent.h"

#include "../GameObject.h"
#include "SkeletonActionComponent.h"

SkeletonStatsComponent::SkeletonStatsComponent(GameObject* skeleton)
{
	this->host = skeleton;
	max_hp = 1000;
	current_hp = max_hp;
	this->damage = 100;
}


SkeletonStatsComponent::~SkeletonStatsComponent()
{
}

void SkeletonStatsComponent::Update()
{
	if (current_hp <= 0) host->action_component->destroy_order = true;
}
