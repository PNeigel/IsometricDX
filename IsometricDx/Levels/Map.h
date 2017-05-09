#pragma once

#include <vector>
#include <SDL.h>

class Tile;
class GameObject;

class Map
{
public:
	Map(SDL_Renderer* renderer, std::vector<SDL_Texture*>* textures);
	~Map();

	void ReadMapData(std::string path);
	void GenerateGroundTexture(SDL_Renderer* renderer, std::vector<SDL_Texture*>* textures);
	void CopyTileOnGround(SDL_Renderer * renderer, SDL_Texture * texture, int sheet_pos, int x, int y);
	void Render(SDL_Renderer* renderer, GameObject* camera);
	void Update() {};

	int width_t, width_px;
	int height_t, height_px;
	std::vector<Tile> ground_tiles; // For every level a list of tiles that make up the level

	SDL_Texture* ground_texture_static = NULL;
};

