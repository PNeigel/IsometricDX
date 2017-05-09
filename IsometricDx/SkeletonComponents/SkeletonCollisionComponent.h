#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\CollisionComponent.h"

class GameObject;
class Level;

class SkeletonCollisionComponent :
	public CollisionComponent
{
public:
	SkeletonCollisionComponent(GameObject* skeleton, Level* level);
	~SkeletonCollisionComponent();

	void ResolveCollisionPlayer(float x_corr, float y_corr);

	void ResolveCollisionBlock(float x_corr, float y_corr);

	void Update();

	void IterateObjects(std::vector<GameObject*> obj_list);

	Level* level;
};

