#pragma once

#include <SDL.h>

class Level;

class IngameState
	// Interface for the Classes IngameRunning, IngamePause, and IngameMenu, Inventory etc
{
public:
	IngameState();
	virtual ~IngameState();

	virtual void Render() {}
	virtual void Update() {}

	Level* level;
};

