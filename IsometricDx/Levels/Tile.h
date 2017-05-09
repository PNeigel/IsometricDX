#pragma once
class Tile {
public:
	Tile(int sheet, int sheet_pos, bool coll);
	Tile(Tile* tile);
	~Tile();
	int GetSheet() { return sheet; }
	int GetNoInSheet() { return sheet_pos; }

private:
	int sheet;
	int sheet_pos;
	bool collision;
};

