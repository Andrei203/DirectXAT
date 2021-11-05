#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game():wnd(800,600,"Game Window")
{
	LoadLevel();
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
	const float t = timer.Time();
	const float r = sin(t) / 2.0f + 0.5f;
	const float g = sin(t+2.0f) / 2.0f + 0.5f;
	const float b = sin(t+4.0f) / 2.0f + 0.5f;
	
	wnd.Rnd().ClearBuffer(r, g, b);

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
	int numX = 0;
	int numY = 0;


	while (!map.eof())
	{
		numX++;
		if (numX == 10)
		{
			numY++;
			numX = 0;
		}
		if (map.get() == blockChar)
		{
			drawables.push_back(std::make_unique<Cube>(wnd.Rnd(), 1.0F, 1.0F, 1.0F, numX * 2 - 10, numY * 2 - 7, 0.0f));
			//wnd.Rnd().DrawTestTriangle(0.0f, numX *2 -10, numY * 2 - 7, 10.0f);
		}
	}
	map.close();
}
