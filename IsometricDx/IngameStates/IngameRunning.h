#pragma once
#include "IngameState.h"

#include <SDL.h>

class Level;
class GameObject;

class IngameRunning :
	public IngameState
{
public:
	IngameRunning(Level* level);
	~IngameRunning();

	void Render();
	void Update();
	void HandleInput();

	void RenderGUI();
	void RenderEnemyHP(GameObject* enemy);
	void RenderPlayerHP();
	void RenderLevel();
};

