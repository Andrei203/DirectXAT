#pragma once
#include "GameTime.h"
#include "Renderer.h"
#include <vector>
#include "Keyboard.h"
class Player
{
public:
	void Update(Keyboard& input, GameTime& timer);
	void Draw(Renderer& Rnd);
	DirectX::XMFLOAT3 player3pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
private:
	float playerRot;
};
