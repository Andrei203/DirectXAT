#include "TextureSampler.h"

TextureSampler::TextureSampler(Renderer& Rnd)
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Rnd.GetDevice()->CreateSamplerState(&samplerDesc, &sampler);
}

void TextureSampler::Bind(Renderer& Rnd)
{
	Rnd.GetContext()->PSSetSamplers(0U, 1U, sampler.GetAddressOf());
}
