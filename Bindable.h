#pragma once
#include "Renderer.h"
class Bindable
{
public:
	virtual void Bind(Renderer& gfx) noexcept = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(Renderer& Rnd) noexcept;
	static ID3D11Device* GetDevice(Renderer& Rnd) noexcept;
};

