#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\CollisionComponent.h"
class FenceCollisionComponent :
	public CollisionComponent
{
public:
	FenceCollisionComponent(GameObject* fence, int sprite_no);
	~FenceCollisionComponent();

	void SetDims(int sprite_no);
};

