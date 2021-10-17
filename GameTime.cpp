#include "GameTime.h"

GameTime::GameTime()
{
	now = std::chrono::steady_clock::now();
	last = now;
	starting = now;
}

void GameTime::Tick()
{
	last = now;
	now = std::chrono::steady_clock::now();
}

float GameTime::DeltaTime()
{
	const std::chrono::duration<float> delta = now - last;
	return delta.count();
}

float GameTime::Time()
{
	const std::chrono::duration<float> delta = now - starting;
	return delta.count();
}


