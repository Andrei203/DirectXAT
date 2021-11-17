#include "Game.h"
#include <iostream>
#include <fstream>
#include "Plane.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Keyboard.h"


Game::Game():wnd(800,600,"Game Window")
{
	LoadLevel();

	drawables.push_back(std::make_unique<Plane>(wnd.Rnd(), 9.0F, 8.0F, 1.0F, 0.0f , -1.0F, 0.0f));
	drawables.push_back(std::make_unique<Plane>(wnd.Rnd(), 9.0F, -8.0F, 1.0F, 0.0f , 1.0F, 0.0f));
	//bullets.push_back(std::make_unique<Bullet>(wnd.Rnd(), 0.10F, 0.10f, 0.10F, player.player3pos.x, player.player3pos.y, player.player3pos.z));
	
}

int Game::init()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}	

		Update(wnd.keyboard);
	}
}

void Game::Update(Keyboard& input)
{
	timer.Tick();
	wnd.keyboard.Tick();
	const float t = timer.Time();
	const float r = sin(t) / 2.0f + 0.5f;
	const float g = sin(t + 2.0f) / 2.0f + 0.5f;
	const float b = sin(t + 4.0f) / 2.0f + 0.5f;

	wnd.Rnd().ClearBuffer(r, g, b);
	auto prevPlayerPos = player.player3pos;
	player.Update(wnd.keyboard, timer);
	player.Draw(wnd.Rnd());

	for (auto& drawable : drawables)
	{
		drawable->Draw(wnd.Rnd());	
	}
	BulletEnemyCollision();
	BulletWallCollision();
	EnemyCollision(prevPlayerPos);
	WallCollision(prevPlayerPos);
	
	if (input.GetKeyDown(0x20))
	{
		bullets.push_back(std::make_unique<Bullet>(wnd.Rnd(), 0.10F, 0.10f, 0.10F, player.player3pos.x, player.player3pos.y, player.player3pos.z, player.playerRot));
	}
	for (auto& bullet : bullets)
	{
		bullet->Update(timer);
		bullet->Draw(wnd.Rnd());
		
	}
	wnd.Rnd().EndFrame();

}


void Game::BulletWallCollision()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		auto& bullet = bullets[i];
		for (size_t j = 0; j < walls.size(); j++)
		{
			auto& wall = walls[j];
			auto x = std::fmaxf(wall->pos.x - 1.0F, std::fminf(bullet->pos.x, wall->pos.x + 1.0F));
			auto z = std::fmaxf(wall->pos.z - 1.0F, std::fminf(bullet->pos.z, wall->pos.z + 1.0F));
			auto distance = std::sqrtf((x - bullet->pos.x) * (x - bullet->pos.x) +
				(z - bullet->pos.z) * (z - bullet->pos.z));
			if (distance < 0.25F && !bullet->isDestroyed)
			{
				bullets.erase(bullets.begin() + i--);
			}
			
		}
	}
}

void Game::BulletEnemyCollision()
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		auto& bullet = bullets[i];
		for (size_t j = 0; j < enemies.size(); j++)
		{
			auto& enemy = enemies[j];

			auto x = std::fmaxf(enemy->pos.x - 0.5f, std::fminf(bullet->pos.x, enemy->pos.x + 0.5F));
			auto z = std::fmaxf(enemy->pos.z - 0.5f, std::fminf(bullet->pos.z, enemy->pos.z + 0.5F));
			auto distance = std::sqrtf((x - bullet->pos.x) * (x - bullet->pos.x) + (z - bullet->pos.z) * (z - bullet->pos.z));
			if (!enemy->isDestroyed && distance < 0.2F)
			{
				enemies.erase(enemies.begin() + j++);
				bullets.erase(bullets.begin() + i--);
				if (enemies.empty())
				{
					wnd.keyboard.inputEnabled = false;
					drawables.push_back(std::make_unique<WinCube>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, player.player3pos.x, player.player3pos.y, player.player3pos.z));
				}
			}
		}
	}
}

void Game::EnemyCollision(DirectX::XMFLOAT3 prevPlayerPos)
{
	for (auto& enemy : enemies)
	{
		
		enemy->playerRotation(player.playerRot);
		auto x = std::fmaxf(enemy->pos.x - 0.5F, std::fminf(player.player3pos.x, enemy->pos.x + 0.5F));
		auto z = std::fmaxf(enemy->pos.z - 0.5F, std::fminf(player.player3pos.z, enemy->pos.z + 0.5F));
		auto distance = std::sqrtf((x - player.player3pos.x) * (x - player.player3pos.x) +
			(z - player.player3pos.z) * (z - player.player3pos.z));
		if (distance < 0.75F)
		{
			player.player3pos.x = 15.0F;
		}
		if (enemy->isDestroyed)
		{
			continue;
		}
		enemy->Draw(wnd.Rnd());
	}
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
			enemies.push_back(std::make_unique<Enemy>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, 0.0F, numY * 2 - 7));
		}
	};
	map.close();
}


