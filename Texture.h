#pragma once
#include "Bindable.h"
#include <string>

class Texture : public Bindable
{
public:
	Texture(Renderer& Rnd, const std::wstring& filepath);
	void Bind(Renderer& Rnd) override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};

