#pragma once
#include <d3d11.h>
#include <vector>
#include<wrl.h>
class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawTestTriangle(float angle);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

