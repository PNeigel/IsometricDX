#include "../PlayerComponents/PlayerActionComponent.h"

#include <iostream>
#include <SDL.h>

#include "../Globals.h"
#include "../Levels/Level.h"
#include "../Components/StatsComponent.h"
#include "../GameObject.h"


PlayerActionComponent::PlayerActionComponent(GameObject* player, Level* level)
{
	this->host = player;
	this->level = level;
}


PlayerActionComponent::~PlayerActionComponent()
{
}

void PlayerActionComponent::Update()
{
	TimerUpdate();
	Run();
	Shoot();
	if (kickback > 0) kickback -= 1;
	if (host->stats_component->current_hp <= 0) destroy_order = true;
}

void PlayerActionComponent::SetOrientation(float xor, float yor)
{
	host->orientation[0] = xor;
	host->orientation[1] = yor;
}

void PlayerActionComponent::SetVelocity(bool run)
{
	if (kickback > 0) host->velocity = -2 * PLAYER_VELOCITY;
	else if (run)
	{
		host->velocity = PLAYER_VELOCITY;
	}
	else {
		host->velocity = 0;
	}
}

void PlayerActionComponent::SetShoot(bool shoot)
{
	// Handle shooting conditions (e.g. cannot shoot while jumping etc.)
	if (shoot) shoot_request = true;
	else shoot_request = false;
}

void PlayerActionComponent::Run()
{
	host->x += host->orientation[0] * host->velocity;
	host->y += host->orientation[1] * host->velocity;
	if (host->x < 0) host->x = 0;
	if (host->y < 0) host->y = 0;
}

void PlayerActionComponent::Shoot()
{
	if (shoot_request && shoot_cooldown == 0) {
		level->CreateProjectile(host->x, host->y, host->z, ARROW_VELOCITY, host->orientation[0], host->orientation[1]);
		shoot_cooldown = 333;
		shoot_request = false;
	}
}

void PlayerActionComponent::TimerUpdate()
{
	if (shoot_cooldown > 0)
	{
		shoot_cooldown -= SDL_GetTicks() - timer;
		if (shoot_cooldown < 0) shoot_cooldown = 0;
	}
	timer = SDL_GetTicks();
}
