#pragma once
#include <chrono>
class GameTime
{
public:
	GameTime();
	void Tick();
	float DeltaTime();
	float Time();
	
private:
	std::chrono::steady_clock::time_point now;
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point starting;
};

