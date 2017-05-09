#pragma once
#include "../Components/StatsComponent.h"

class GameObject;

class SkeletonStatsComponent :
	public StatsComponent
{
public:
	SkeletonStatsComponent(GameObject* skeleton);
	~SkeletonStatsComponent();

	void Update();
};

