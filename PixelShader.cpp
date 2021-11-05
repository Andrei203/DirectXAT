#include "PixelShader.h"
#include <d3dcompiler.h>


PixelShader::PixelShader(Renderer& Rnd, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(path.c_str(), &blob);
	Rnd.GetDevice()->CreatePixelShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&pPixelShader
	);
}

void PixelShader::Bind(Renderer& Rnd)
{
	Rnd.GetContext()->PSSetShader(
		pPixelShader.Get(),
		nullptr,
		0U
	);
}
