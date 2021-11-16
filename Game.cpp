#include "Game.h"
#include <iostream>
#include <fstream>
#include "Plane.h"
#include "Enemy.h"

Game::Game():wnd(800,600,"Game Window")
{
	LoadLevel();

	drawables.push_back(std::make_unique<Plane>(wnd.Rnd(), 9.0F, 8.0F, 1.0F, 0.0f , -1.0F, 0.0f));
	drawables.push_back(std::make_unique<Plane>(wnd.Rnd(), 9.0F, -8.0F, 1.0F, 0.0f , 1.0F, 0.0f));
	
}

int Game::init()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}	
		
		Update();
	}

}

void Game::Update()
{
	timer.Tick();
	wnd.keyboard.Tick();
	const float t = timer.Time();
	const float r = sin(t) / 2.0f + 0.5f;
	const float g = sin(t+2.0f) / 2.0f + 0.5f;
	const float b = sin(t+4.0f) / 2.0f + 0.5f;	
	
	wnd.Rnd().ClearBuffer(r, g, b);
	auto prevPlayerPos = player.player3pos;
	player.Update(wnd.keyboard, timer);
	player.Draw(wnd.Rnd());
	for (auto& drawable : drawables)
	{
		drawable->Draw(wnd.Rnd());
	}
	
	WallCollision(prevPlayerPos);
	wnd.Rnd().EndFrame();
	
}
void Game::WallCollision(DirectX::XMFLOAT3 prevPlayerPos)
{
	
	for (auto& wall : walls)
	{
		auto x = std::fmaxf(wall->pos.x - 1.0F, std::fminf(player.player3pos.x, wall->pos.x + 1.0F));
		auto z = std::fmaxf(wall->pos.z - 1.0F, std::fminf(prevPlayerPos.z, wall->pos.z + 1.0F));
		auto distance = std::sqrtf((x - player.player3pos.x) * (x - player.player3pos.x) +
			(z - prevPlayerPos.z) * (z - prevPlayerPos.z));
		if (distance < 0.75F)
		{
			player.player3pos.x = prevPlayerPos.x;
		}

		x = std::fmaxf(wall->pos.x - 1.0F, std::fminf(prevPlayerPos.x, wall->pos.x + 1.0F));
		z = std::fmaxf(wall->pos.z - 1.0F, std::fminf(player.player3pos.z, wall->pos.z + 1.0F));
		distance = std::sqrtf((x - prevPlayerPos.x) * (x - prevPlayerPos.x) +
			(z - player.player3pos.z) * (z - player.player3pos.z));
		if (distance < 0.75F)
		{
			player.player3pos.z = prevPlayerPos.z;
		}

		wall->Draw(wnd.Rnd());
	}
}
void Game::LoadLevel()
{
	std::fstream map;
	map.open("TestMap.txt");
	char blockChar = '#';
	char EnemyChar = 'E';
	
	int numX = 0;
	int numY = 0;


	while (!map.eof())
	{
		char c = map.get();
		numX++; 
			if (numX == 10)
			{
				numY++;
				numX = 0;
			};
		if (c == blockChar)
		{
			walls.push_back(std::make_unique<Cube>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, 0.0F, numY * 2 - 7));
			//wnd.Rnd().DrawTestTriangle(0.0f, numX *2 -10, numY * 2 - 7, 10.0f);
		}
		else if (c == EnemyChar)
		{
			drawables.push_back(std::make_unique<Enemy>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, 0.0F, numY * 2 - 7));
		}
	};
	map.close();
}


