#pragma once
#include "Drawable.h"
#include "GameTime.h"
#include "Renderer.h"
#include <vector>

class Enemy : public Drawable
{
public:
	Enemy(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX = 0.0F, float offsetY = 0.0F, float offsetZ = 0.0F);
	void Draw(Renderer& Rnd) override;
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	void Update();
private:
	GameTime timer;
};


