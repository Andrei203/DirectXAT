#pragma once
#include "Bindable.h"
#include <string>

class PixelShader : public Bindable
{
public:
	PixelShader(Renderer& Rnd, const std::wstring& path);
	void Bind(Renderer& Rnd) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};