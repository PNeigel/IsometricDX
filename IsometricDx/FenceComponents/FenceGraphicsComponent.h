#pragma once
#include "D:\Programming\IsometricDx\IsometricDx\Components\GraphicsComponent.h"
class FenceGraphicsComponent :
	public GraphicsComponent
{
public:
	FenceGraphicsComponent(GameObject* fence, SDL_Texture* sprite_sheet, int sprite_no);
	~FenceGraphicsComponent();
};

