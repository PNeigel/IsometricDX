#pragma once

#include <vector>

class GameObject;

class CollisionComponent
{
public:

	enum {
		UP_COLLISION,
		UP_OVERLAP,
		LEFT_COLLISION,
		LEFT_OVERLAP,
		DOWN_COLLISION,
		DOWN_OVERLAP,
		RIGHT_COLLISION,
		RIGHT_OVERLAP,
	};

	virtual ~CollisionComponent() {}

	virtual void Update() {}

	bool CheckCollision(GameObject* target, float& x_corr, float& y_corr);
	virtual void ResolveCollision(GameObject* target);

	virtual void UpdatePosition();

	GameObject* host;

	float box_x;
	float box_y;
	float box_w;
	float box_h;
};