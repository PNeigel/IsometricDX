#include "Map.h"

#include "../Globals.h"
#include "Tile.h"
#include "../GameObject.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

Map::Map(SDL_Renderer* renderer, std::vector<SDL_Texture*>* textures)
{
	width_t = 0;
	height_t = 0;
	ReadMapData("Assets/Maps/map1.xml");
	GenerateGroundTexture(renderer, textures);
}


Map::~Map()
{
	SDL_DestroyTexture(ground_texture_static);
	std::cout << "Deleting map..." << std::endl;
}

void Map::ReadMapData(std::string path)
{
	std::string line, wordstring;
	std::stringstream linestream;
	std::ifstream map_file(path.c_str()); // Open Level.txt
	std::smatch match;

	std::cout << "Attempting to read map data..." << std::endl;

	if (map_file)
	{
		std::cout << "MapFile opened successfully." << std::endl;
		// Get Width
		std::getline(map_file, line);
		while (line != "<map>") std::getline(map_file, line);
		while (!std::regex_search(line, std::regex("<width>"))) std::getline(map_file, line);
		std::getline(map_file, line);
		linestream = std::stringstream(line);
		linestream >> width_t;
		// Get Height
		while (!std::regex_search(line, std::regex("<height>"))) std::getline(map_file, line);
		std::getline(map_file, line);
		linestream = std::stringstream(line);
		linestream >> height_t;
		ORIGIN = (height_t - 1) * TILE_SIZE / 2;
		
		// Go to Ground and Parse
		while (!std::regex_search(line, std::regex("<ground>"))) std::getline(map_file, line);
		for (int i = 0; i < height_t; i++) // Read all Rows
		{
			std::getline(map_file, line);
			linestream = std::stringstream(line);
			for (int j = 0; j < width_t; j++) // Read every tile in the row
			{
				linestream >> wordstring;
				int params[3];
				for (int k = 0; k < 3; k++) // Parse Sheet(0), Sheet_pos(1) and collision(2)
				{
					std::regex_search(wordstring, match, std::regex("\\d+"));
					params[k] = std::stoi(match[0]);
					wordstring = match.suffix();
				}
				bool collision = !(bool)(params[2] - 1); // Sets everything to false except 1
				ground_tiles.push_back(new Tile(params[0], params[1], collision));
			}
		}
		map_file.close();
		std::cout << "Ground loaded successfully!" << std::endl;

	}
	else
	{
		std::cerr << "Error while loading Map: " << strerror(errno);
	}
	
}

void Map::GenerateGroundTexture(SDL_Renderer* renderer, std::vector<SDL_Texture*>* textures)
{
	int total_size_tiles = (width_t) * (height_t);

	width_px = (width_t + height_t) * TILE_SIZE / 2;
	height_px = (0.5 * (width_t + height_t) + 1) * TILE_SIZE / 2;

	Uint32 pixelformat;
	SDL_QueryTexture((*textures)[0], &pixelformat, NULL, NULL, NULL); // Make sure texture has same pixelformat as sourcetexture (probably tilesheet)
	// Create map texture
	ground_texture_static = SDL_CreateTexture(renderer, pixelformat, SDL_TEXTUREACCESS_TARGET, width_px, height_px);
	SDL_SetTextureBlendMode(ground_texture_static, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, ground_texture_static);

	// Get RenderDrawColor so we can set it back in the end
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	// Set RenderDrawColor black so the void surrounding the map is black
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	// Clear Renderer so we draw only the map and don't  take anything from before with us
	SDL_RenderClear(renderer);
	
	int current_tile;
	// i,j are in tile coordinates
	for (int i = 0; i < width_t; i++) {

		for (int j = 0; j < height_t; j++) {

			current_tile = i + j*width_t;

			if (current_tile < total_size_tiles && current_tile >= 0) {
				CopyTileOnGround(renderer, (*textures)[ground_tiles[current_tile].GetSheet()], ground_tiles[current_tile].GetNoInSheet(), i, j);
			}
		}
	}
	std::cout << "Successfully generated ground texture!" << std::endl;

	SDL_SetRenderTarget(renderer, nullptr);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Map::CopyTileOnGround(SDL_Renderer * renderer, SDL_Texture * texture, int sheet_pos, int x, int y)
{
	SDL_Rect srcrect, dstrect;

	// Source Rectangle
	srcrect.x = (sheet_pos % SHEET_WIDTH) * TILE_SIZE;
	srcrect.y = (sheet_pos / SHEET_WIDTH) * TILE_SIZE;
	srcrect.w = TILE_SIZE;
	srcrect.h = TILE_SIZE;

	// Destination Rectangle
	dstrect.x = (x - y + height_t - 1) * TILE_SIZE / 2;
	dstrect.y = (x + y) * TILE_SIZE / 4;
	dstrect.w = TILE_SIZE;
	dstrect.h = TILE_SIZE;
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void Map::Render(SDL_Renderer* renderer, GameObject* camera)
{
	SDL_Rect srcrect, dstrect;

	int x = round(camera->x);
	int y = round(camera->y);
	int offset_x = 0;
	int offset_y = 0;// Offsets are for rendering when camera goes off texture

	if (x < 0)
	{
		offset_x = -x;
		x = 0;

	}
	if (x + SCREEN_WIDTH > width_px)
	{
		offset_x = -(x + SCREEN_WIDTH - width_px);
		x = width_px - SCREEN_WIDTH;
	}
	if (y < 0)
	{
		offset_y = -y;
		y = 0;
	}
	if (y + SCREEN_HEIGHT > height_px)
	{
		offset_y = -(y + SCREEN_HEIGHT - height_px);
		y = height_px - SCREEN_HEIGHT;
	}

	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = SCREEN_WIDTH;
	srcrect.h = SCREEN_HEIGHT;

	dstrect.x = offset_x;
	dstrect.y = offset_y;
	dstrect.w = SCREEN_WIDTH;
	dstrect.h = SCREEN_HEIGHT;

	SDL_RenderCopy(renderer, ground_texture_static, &srcrect, &dstrect);
}
