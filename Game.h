#pragma once
#include "Window.h"
#include "GameTime.h"
#include "Cube.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Keyboard.h"
#include "WinCube.h"
class Game
{
public:
	Game();
	int init();
private:
	void Update(Keyboard& input);
	void LoadLevel();
	void WallCollision(DirectX::XMFLOAT3 prevPlayerPos);
	void EnemyCollision(DirectX::XMFLOAT3 prevPlayerPos);
	void BulletWallCollision();
	void BulletEnemyCollision();
private:
	Window wnd;
	GameTime timer;
	Player player;
	std::vector<std::unique_ptr<Drawable>> drawables;
	std::vector<std::unique_ptr<Cube>> walls;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Bullet>> bullets;
};

