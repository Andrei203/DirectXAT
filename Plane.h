#pragma once
#include "Drawable.h"
class Plane : public Drawable
{
public:
	Plane(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX = 0.0F, float offsetY = 0.0F, float offsetZ = 0.0F);
	void Draw(Renderer& Rnd) override;
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();
};

