#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\GraphicsComponent.h"
class SkeletonGraphicsComponent :
	public GraphicsComponent
{
public:
	SkeletonGraphicsComponent(GameObject* skeleton, SDL_Texture* sprite_sheet, int sprite_no);
	~SkeletonGraphicsComponent();
};

