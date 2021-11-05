#pragma once
#include "Window.h"
#include "GameTime.h"
#include "Cube.h"
class Game
{
public:
	Game();
	int init();
private:
	void Update();
	void LoadLevel();
private:
	Window wnd;
	GameTime timer;
	std::vector<std::unique_ptr<Drawable>> drawables;
};

