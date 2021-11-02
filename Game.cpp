#include "Game.h"
#include <iostream>
#include <fstream>

Game::Game():wnd(800,600,"Game Window")
{
	
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
			wnd.Rnd().DrawTestTriangle(0.0f, numX *2 -10, numY * 2 - 7, 10.0f);
		}
	}
	map.close();
	
	wnd.Rnd().EndFrame();
}
