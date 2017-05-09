#pragma once
#include "../Components/StatsComponent.h"

class GameObject;

class PlayerStatsComponent :
	public StatsComponent
{
public:
	PlayerStatsComponent(GameObject* player);
	~PlayerStatsComponent();
};

