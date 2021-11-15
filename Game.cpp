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
	player.Update(wnd.keyboard, timer);
	player.Draw(wnd.Rnd());
	for (auto& drawable : drawables)
	{
		drawable->Draw(wnd.Rnd());
	}

	wnd.Rnd().EndFrame();
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
			drawables.push_back(std::make_unique<Cube>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, 0.0F, numY * 2 - 7));
			//wnd.Rnd().DrawTestTriangle(0.0f, numX *2 -10, numY * 2 - 7, 10.0f);
		}
		else if (c == EnemyChar)
		{
			drawables.push_back(std::make_unique<Enemy>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, 0.0F, numY * 2 - 7));
		}
	};

	map.close();
}
