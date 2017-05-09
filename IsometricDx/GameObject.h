#pragma once

#include <SDL.h>

class ActionComponent;
class CollisionComponent;
class GraphicsComponent;
class InputComponent;
class StatsComponent;

class GameObject
{
public:
	GameObject(ActionComponent* action_component,
				CollisionComponent* collision_component,
				GraphicsComponent* graphics_component,
				InputComponent* input_component,
				StatsComponent* stats_component);
	GameObject(float x, float y, float z, float velocity, float orientationx, float orientationy);
	~GameObject();

	float x, y, z;
	float velocity;
	float orientation[2];

	void Update();
	void Render(SDL_Renderer* renderer, GameObject* camera);
	
	float DistanceFromOrigin();

	ActionComponent* action_component;
	CollisionComponent* collision_component;
	GraphicsComponent* graphics_component;
	InputComponent* input_component;
	StatsComponent* stats_component;
	
};

