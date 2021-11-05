#pragma once
#include <DirectXMath.h>
#include "Renderer.h"

class ConstantBuffer
{
public:
	struct ConstantBufferData
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	ConstantBuffer(Renderer& Rnd, const ConstantBufferData& bufferData);
	void Bind(Renderer& Rnd, const ConstantBufferData& bufferData);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
};
/*template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Renderer& Rnd, const C& consts)
	{
		(Rnd);

		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(Rnd)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(Rnd)->Unmap(pConstantBuffer.Get(), 0u);
	}
	ConstantBuffer(Renderer& Rnd, const C& consts)
	{
		(Rnd);

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GetDevice(Rnd)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}
	ConstantBuffer(Renderer& Rnd)
	{
		(Rnd);

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GetDevice(Rnd)->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& Rnd) noexcept override
	{
		GetContext(Rnd)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& Rnd) noexcept override
	{
		GetContext(Rnd)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};*/