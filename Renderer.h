#pragma once
#include <d3d11.h>
#include <vector>
#include<wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include "ConstantBuffers.h"

class Renderer
{
	friend class Bindable;
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	void SetModelMatrix(DirectX::XMMATRIX model);
	void SetViewMatrix(DirectX::XMMATRIX view);

	std::unique_ptr<ConstantBuffer> constantBuffer;
	ConstantBuffer::ConstantBufferData constantBufferData;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};


