#include "Tile.h"


Tile::Tile(int sheet, int sheet_pos, bool coll) {
	this->sheet = sheet;
	this->sheet_pos = sheet_pos;
	this->collision = coll;
}

Tile::Tile(Tile * tile)
{
	this->sheet = tile->sheet;
	this->sheet_pos = tile->sheet_pos;
	this->collision = tile->collision;
}

Tile::~Tile()
{
}