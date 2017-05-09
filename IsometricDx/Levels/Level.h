#pragma once

#include <string>
#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>

class IngameState;
class Map;
class Enemy;
class GameObject;
class Game;

class Level
{
public:
	Level(Game* game, SDL_Renderer* renderer);
	~Level();

	void RenderIngameState();
	void RenderAssets();
	void UpdateIngameState();
	void UpdateAssets();

	void ReturnToMainMenu();

	void CreatePlayer();
	void CreateCamera();
	void CreateProjectile(float x, float y, float z, float velocity, float orientationx, float orientationy);
	void CreateSkeleton(float x, float y, float z, float velocity, float orientationx, float orientationy);
	void CreateFence(float x, float y, float z, int sheet_no, int sheet_pos);

	void DestroyObject(GameObject* obj);
	void DestroyObject(std::vector<GameObject*> &obj_list);

	void LoadAddTexture(std::string path);
	void LoadAudio();

	Game* game;
	SDL_Renderer* renderer;

	IngameState* ingamestate;
	IngameState* runningstate;
	IngameState* menustate;

	Map* map = nullptr;
	GameObject* player = nullptr;
	GameObject* camera = nullptr;

	std::vector<GameObject*> projectiles;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> statics;
	
	std::vector<SDL_Texture*> sprite_sheets;

	Mix_Music* music_bg = nullptr;

	int menu_cd = 0;
};

bool CompareObjectDistance(GameObject* a, GameObject* b);

