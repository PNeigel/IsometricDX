#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\CollisionComponent.h"

#include <vector>

class GameObject;
class Level;

class PlayerCollisionComponent :
	public CollisionComponent
{
public:
	PlayerCollisionComponent(GameObject* player, Level* level);
	~PlayerCollisionComponent();

	void ResolveCollisionStatic(float x_corr, float y_corr);
	void IterateObjects(std::vector<GameObject*> obj_list);

	void Update();

	Level* level;
};

