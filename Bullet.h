#pragma once
#include "Drawable.h"
#include "GameTime.h"
#include "Renderer.h"
#include "Player.h"
#include <vector>

class Bullet : public Drawable
{
public:
	Bullet(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX = 0.0F, float offsetY = 0.0F, float offsetZ = 0.0F);
	void Draw(Renderer& Rnd) override;
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT3 velocity = DirectX::XMFLOAT3(0.0f, 0.0f, 2.5f);
	
	void Update(GameTime& time);
};
