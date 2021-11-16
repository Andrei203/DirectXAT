#pragma once
#include "Window.h"
#include "GameTime.h"
#include "Cube.h"
#include "Player.h"
class Game
{
public:
	Game();
	int init();
private:
	void Update();
	void LoadLevel();
	void WallCollision(DirectX::XMFLOAT3 prevPlayerPos);
private:
	Window wnd;
	GameTime timer;
	Player player;
	std::vector<std::unique_ptr<Drawable>> drawables;
	std::vector<std::unique_ptr<Cube>> walls;
};

