#include "GameObject.h"

#include <math.h>

#include "./Components/InputComponent.h"
#include "./Components/GraphicsComponent.h"
#include "./Components/CollisionComponent.h"
#include "./Components/ActionComponent.h"
#include "./Components/StatsComponent.h"

#include <iostream>

GameObject::GameObject(ActionComponent* action_component,
	CollisionComponent* collision_component,
	GraphicsComponent* graphics_component,
	InputComponent* input_component,
	StatsComponent* stats_component)
{
	this->action_component = action_component;
	this->collision_component = collision_component;
	this->graphics_component = graphics_component;
	this->input_component = input_component;
	this->stats_component = stats_component;
	x = 0;
	y = 0;
	z = 0;
	velocity = 0;
	orientation[0] = 1;
	orientation[1] = 0;
}

GameObject::GameObject(float x, float y, float z, float velocity, float orientationx, float orientationy)
	:x(x), y(y), z(z), velocity(velocity)
{
	this->orientation[0] = orientationx;
	this->orientation[1] = orientationy;
	this->action_component = nullptr;
	this->collision_component = nullptr;
	this->graphics_component = nullptr;
	this->input_component = nullptr;
	this->stats_component = nullptr;
}


GameObject::~GameObject()
{
	std::cout << "Deleting GameObject" << std::endl;
	delete action_component;
	delete collision_component;
	delete graphics_component;
	delete input_component;
	delete stats_component;
}

void GameObject::Update()
{
	if (input_component != nullptr) input_component->Update();
	if (action_component != nullptr) action_component->Update();
	if (collision_component != nullptr) collision_component->Update();
	if (stats_component != nullptr) stats_component->Update();
}

void GameObject::Render(SDL_Renderer* renderer, GameObject* camera)
{
	graphics_component->Render(renderer, camera);
}

float GameObject::DistanceFromOrigin()
{
	return sqrt(pow(x, 2)+pow(y,2));
}
