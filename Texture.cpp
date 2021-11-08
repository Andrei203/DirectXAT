#include "Texture.h"
#include "TextureLoader.h"
Texture::Texture(Renderer& Rnd, const std::wstring& filepath)
{
	auto result = DirectX::CreateWICTextureFromFile(Rnd.GetDevice(), filepath.c_str(), NULL, &shaderResourceView);
	assert(SUCCEEDED(result));
	
}

void Texture::Bind(Renderer& Rnd)
{
	Rnd.GetContext()->PSGetShaderResources
	(
		0U,
		1U,
		shaderResourceView.GetAddressOf()
	);
}
