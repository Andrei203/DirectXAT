#include "VertexShader.h"

VertexShader::VertexShader(Renderer& Rnd, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	Rnd.GetDevice()->CreateInputLayout(
		layout.data(),
		static_cast<unsigned int>(layout.size()),
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		&pInputLayout
	);
	Rnd.GetDevice()->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
}

void VertexShader::Bind(Renderer& Rnd)
{
	Rnd.GetContext()->IASetInputLayout(pInputLayout.Get());
	Rnd.GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}
