#pragma once
#include "Drawable.h"
class Cube : public Drawable
{
public:
	Cube(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX = 0.0F, float offsetY = 0.0F, float offsetZ = 0.0F);
	void Draw(Renderer& Rnd) override;
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT3 pos;
};

