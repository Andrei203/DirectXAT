#include "ConstantBuffers.h"

ConstantBuffer::ConstantBuffer(Renderer& Rnd, const ConstantBufferData& bufferData)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.ByteWidth = sizeof(bufferData);
	bufferDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = &bufferData;
	Rnd.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &constantBuffer);
}

void ConstantBuffer::Bind(Renderer& Rnd, const ConstantBufferData& bufferData)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	Rnd.GetContext()->Map(
		constantBuffer.Get(),
		0U,
		D3D11_MAP_WRITE_DISCARD,
		0U,
		&mappedSubresource
	);
	memcpy(mappedSubresource.pData, &bufferData, sizeof(bufferData));
	auto* ctx = Rnd.GetContext();
	ctx->Unmap(constantBuffer.Get(), 0U);

	ctx->VSSetConstantBuffers(
		0U,
		1U,
		constantBuffer.GetAddressOf()
	);
}
