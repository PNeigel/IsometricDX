#pragma once

class GameObject;

class StatsComponent
{
public:
	StatsComponent();
	~StatsComponent();

	virtual void Update() {}

	GameObject* host;

	int max_hp;
	int current_hp;
	int damage;
};

