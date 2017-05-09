#include "Level.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../CameraComponents/CameraKeyInputComponent.h"
#include "../CameraComponents/CameraFollowActionComponent.h"
#include "../PlayerComponents/PlayerGraphicsComponent.h"
#include "../PlayerComponents/PlayerInputComponent.h"
#include "../PlayerComponents/PlayerActionComponent.h"
#include "../PlayerComponents/PlayerStatsComponent.h"
#include "../PlayerComponents/PlayerCollisionComponent.h"
#include "../ProjectileComponents/ProjectileActionComponent.h"
#include "../ProjectileComponents/ProjectileGraphicsComponent.h"
#include "../ProjectileComponents/ProjectileCollisionComponent.h"
#include "../SkeletonComponents/SkeletonGraphicsComponent.h"
#include "../SkeletonComponents/SkeletonCollisionComponent.h"
#include "../SkeletonComponents/SkeletonActionComponent.h"
#include "../SkeletonComponents/SkeletonStatsComponent.h"
#include "../FenceComponents/FenceCollisionComponent.h"
#include "../FenceComponents/FenceGraphicsComponent.h"
#include "../IngameStates/IngameState.h"
#include "../IngameStates/IngameRunning.h"
#include "../IngameStates/IngameMenu.h"
#include "../Levels/Map.h"
#include "../GameObject.h"
#include "../Globals.h"
#include "../EngineStates/Game.h"
#include "../GameStates/GameMainMenu.h"

Level::Level(Game* game, SDL_Renderer* renderer)
{
	this->game = game;
	this->renderer = renderer;

	LoadAddTexture("Assets/Sprites/sheet1.png");
	LoadAddTexture("Assets/Sprites/man.png");
	LoadAddTexture("Assets/Sprites/skeleton.png");
	LoadAddTexture("Assets/Sprites/Gui.png");

	map = new Map(renderer, &sprite_sheets);
	// Create level, temporarily in this class and manually

	CreatePlayer();
	CreateCamera();
	for (int i = 0; i < 4; i++)
	{
		CreateSkeleton(3*64, (6+i) * 64, 0, 0, 0, 0);
	}
	for (int i = 3; i < 8; i++)
	{
		CreateFence(i * 64, 4 * 64, 0, 0, 49);
		CreateFence(i * 64, 12 * 64, 0, 0, 53);
	}
	for (int i = 5; i < 12; i++)
	{
		CreateFence(2 * 64, i * 64, 0, 0, 51);
		if (i != 8) CreateFence(8 * 64, i * 64, 0, 0, 55);
	}
	// Corner posts
	CreateFence(2 * 64, 4 * 64, 0, 0, 43);
	CreateFence(2 * 64, 12 * 64, 0, 0, 47);
	CreateFence(8 * 64, 4 * 64, 0, 0, 45);
	CreateFence(8 * 64, 12 * 64, 0, 0, 41);

	runningstate = new IngameRunning(this);
	menustate = new IngameMenu(this);
	ingamestate = runningstate;
	LoadAudio();
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
	Mix_PlayMusic(music_bg, -1);
}


Level::~Level()
{
	delete map;
	delete camera;
	delete player;
	for (auto texture : sprite_sheets)
	{
		SDL_DestroyTexture(texture);
	}
	for (auto projectile : projectiles)
	{
		delete projectile;
	}
	for (auto enemy : enemies)
	{
		delete enemy;
	}
	for (auto static_obj : statics)
	{
		delete static_obj;
	}
	Mix_HaltMusic();
	Mix_FreeMusic(music_bg);
	ingamestate = nullptr;
	delete runningstate;
	delete menustate;
	std::cout << "Deleting Level and Spritesheets..." << std::endl;
}

void Level::RenderIngameState()
{
	ingamestate->Render();
}

void Level::RenderAssets()
{
	map->Render(renderer, camera);

	std::vector<GameObject*> all;
	all.insert(all.end(), projectiles.begin(), projectiles.end());
	all.insert(all.end(), enemies.begin(), enemies.end());
	all.insert(all.end(), statics.begin(), statics.end());
	all.insert(all.end(), player);

	std::sort(all.begin(), all.end(), CompareObjectDistance);

	for (auto obj : all)
	{
		obj->Render(renderer, camera);
	}
}

void Level::UpdateIngameState()
{
	ingamestate->Update();
}

void Level::UpdateAssets()
{
	map->Update();
	player->Update();
	camera->Update();
	for (auto obj : projectiles) {
		obj->Update();
	}
	for (auto obj : enemies) {
		obj->Update();
	}
	DestroyObject(projectiles);
	DestroyObject(enemies);
	if (player->action_component->destroy_order) ReturnToMainMenu();
}

void Level::ReturnToMainMenu()
{
	GameState* gamerunning = game->gamestate;
	game->gamestate = new GameMainMenu(game, renderer);
	delete gamerunning;
}

void Level::CreatePlayer()
{
	player = new GameObject(nullptr, nullptr, nullptr, nullptr, nullptr);
	PlayerGraphicsComponent* playergraphics = new PlayerGraphicsComponent(player, sprite_sheets[1], 0);
	PlayerInputComponent* playerinput = new PlayerInputComponent(player);
	PlayerActionComponent* playeraction = new PlayerActionComponent(player, this);
	player->graphics_component = playergraphics;
	player->input_component = playerinput;
	player->action_component = playeraction;
	player->collision_component = new PlayerCollisionComponent(player, this);
	player->stats_component = new PlayerStatsComponent(player);
}

void Level::CreateCamera()
{
	camera = new GameObject(nullptr, nullptr, nullptr, nullptr, nullptr);
	CameraFollowActionComponent* camfollow = new CameraFollowActionComponent(camera, player);
	camera->action_component = camfollow;
}

void Level::CreateProjectile(float x, float y, float z, float velocity, float orientationx, float orientationy)
{
	GameObject* projectile = new GameObject(x, y, z, ARROW_VELOCITY, orientationx, orientationy);
	projectile->action_component = new ProjectileActionComponent(projectile, this);
	projectile->graphics_component = new ProjectileGraphicsComponent(projectile, sprite_sheets[0], 14);
	projectile->collision_component = new ProjectileCollisionComponent(projectile, this);
	projectiles.push_back(projectile);
}

void Level::CreateSkeleton(float x, float y, float z, float velocity, float orientationx, float orientationy)
{
	GameObject* skeleton = new GameObject(x, y, z, SKELETON_VELOCITY, orientationx, orientationy);
	skeleton->graphics_component = new SkeletonGraphicsComponent(skeleton, sprite_sheets[2], 0);
	skeleton->collision_component = new SkeletonCollisionComponent(skeleton, this);
	skeleton->action_component = new SkeletonActionComponent(skeleton, this);
	skeleton->stats_component = new SkeletonStatsComponent(skeleton);
	enemies.push_back(skeleton);

	
}

void Level::CreateFence(float x, float y, float z, int sheet_no, int sheet_pos)
{
	GameObject* fence = new GameObject(x, y, z, 0, 0, 0);
	fence->graphics_component = new FenceGraphicsComponent(fence, sprite_sheets[sheet_no], sheet_pos);
	fence->collision_component = new FenceCollisionComponent(fence, sheet_pos);
	statics.push_back(fence);
}

void Level::DestroyObject(GameObject * obj)
{
	if (obj->action_component->destroy_order) delete obj;
}

void Level::DestroyObject(std::vector<GameObject*> &obj_list)
{
	for (int i = 0; i < obj_list.size(); i++)
	{
		if (obj_list[i]->action_component != nullptr && obj_list[i]->action_component->destroy_order)
		{
			delete obj_list[i];
			obj_list.erase(obj_list.begin() + i);
			i -= 1;
			std::cout << obj_list.size() << std::endl;

		}
	}
}

void Level::LoadAddTexture(std::string path)
{
	SDL_Surface* temp_surface = IMG_Load(path.c_str());
	SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
	sprite_sheets.push_back(temp_texture);
	SDL_FreeSurface(temp_surface);
}

void Level::LoadAudio()
{
	music_bg = Mix_LoadMUS("Assets/Music/ActionFight.mp3");
	if (music_bg == nullptr)
	{
		std::cout << "Music not loaded:" << Mix_GetError() << std::endl;
	}
	else std::cout << "Music loaded successfully" << std::endl;
}

bool CompareObjectDistance(GameObject* a, GameObject* b)
{
	return (a->DistanceFromOrigin() < b->DistanceFromOrigin());
}
