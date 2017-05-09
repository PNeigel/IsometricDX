#pragma once
#include <math.h>

static int SCREEN_WIDTH = 1366; // Pixels
static int SCREEN_HEIGHT = 768; // Pixels

static int TILE_SIZE = 128; // In pixels
static int SHEET_WIDTH = 8; // In Tiles

static int CAMERA_VELOCITY = 20;
static int PLAYER_VELOCITY = 6;
static int SKELETON_VELOCITY = 3;
static int ARROW_VELOCITY = 20;
extern int ORIGIN;

static void GameToScreen(float x_game, float y_game, int& x_screen, int& y_screen) {
	// Convert from GAME COORDINATES to SCREEN COORDINATES
	x_screen = (int)round(x_game - y_game);
	y_screen = (int)round((x_game + y_game) / double(2));
}

static void ScreenToGame(int x_screen, int y_screen, float& x_game, float& y_game)
{
	// Convert from SCREEN COORDINATES to GAME COORDINATES
	x_game = 0.5 * x_screen + y_screen;
	y_game = -0.5 * x_screen + y_screen;
}

static void SetResolution(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}


