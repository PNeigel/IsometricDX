#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\ActionComponent.h"

class GameObject;
class Level;

class SkeletonActionComponent :
	public ActionComponent
{
public:
	SkeletonActionComponent(GameObject* skeleton, Level* level);
	~SkeletonActionComponent();

	void Update();
	void Move();

	void ApplyDamage(GameObject * target, int damage);

	Level* level;
};

