#pragma once
#include "Bindable.h"
class TextureSampler: public Bindable
{
public:
	TextureSampler(Renderer& Rnd);
	void Bind(Renderer& Rnd) override;
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

