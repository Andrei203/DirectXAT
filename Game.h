#pragma once
#include "Window.h"
#include "GameTime.h"
class Game
{
public:
	Game();
	int init();
private:
	void Update();
private:
	Window wnd;
	GameTime timer;

};

