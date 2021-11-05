#include "VertexShader.h"
void VertexShader::Bind(Renderer& Rnd) noexcept
{
	GetContext(Rnd)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}