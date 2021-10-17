#include "Game.h"

Game::Game():wnd(640,480,"Game Window")
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
	wnd.Rnd().DrawTestTriangle();
	wnd.Rnd().EndFrame();
}
