#include "PixelShader.h"


PixelShader::PixelShader(Renderer& Rnd, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	GetDevice(Rnd)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
}

void PixelShader::Bind(Renderer& Rnd) noexcept
{
	GetContext(Rnd)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
