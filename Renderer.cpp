#include "Renderer.h"
#include <d3dcompiler.h>
#include <sstream>
#include <cmath>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	//device for front/back buffers, renderer and swap chain.
	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	//acess to texture subresource, back buffer

	ID3D11Resource* pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView
	(
		pBackBuffer,
		nullptr,
		&pTarget
	);
	pBackBuffer->Release();
}

void Renderer::ClearBuffer(float red, float green, float blue) noexcept
{
	const float colour[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), colour);
}
void Renderer::DrawTestTriangle(float angle)
{
	namespace wrl = Microsoft::WRL;
	
	struct Vertex
	{
		struct {
			float x;
			float y;
			float z;
		}position;

		struct {
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		}color;
	};
	//create vertex buffer ( 1 2d triangle)
	Vertex vertices[] =
	{
		{-1.0f,-1.0f,1 - .0f, 255,0,0},
		{1.0f,-1.0f,-1.0f,  0,255,0},
		{-1.0f,1.0f,-1.0f,  0,0,255},
		{1.0f,1.0f,-1.0f,	255,255,0},
		{-1.0f,-1.0f,1.0f,	255,0,255},
		{1.0f,-1.0f,1.0f,	0,255,255},
		{-1.0f,1.0f,1.0f,	0,0,0},
		{1.0f,1.0f,1.0f,	255,255,255},
	};

	vertices[0].color.g = 255;
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);



	//vertex to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset);

	//creating index buffer
	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4,
	};
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	// bind index buffer
	pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
	
	//creating constant buffer for transformation matrix
	struct ConstantBuffer
	{
		dx::XMMATRIX transform;
	};

	const ConstantBuffer cb =
	{
		{
			dx::XMMatrixTranspose(
				dx::XMMatrixRotationZ(angle) *
				//dx::XMMatrixRotationX(angle) *
				dx::XMMatrixScaling(3.0f / 4.0f,1.0f, 1.0f) *
				dx::XMMatrixTranslation(3.0f / 4.0f, 1.0f, 0.0f)
				//dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 1.0f,5.0f)
			)
		}
	};

	//constant buffer
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;

	// bind constant buffer to vertex shader
	pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	//create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//bind pixel shader
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
	
	//create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	//bind vertex shader
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);
	
	//input vertext layout 2D POS only
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	
	// bind vertex layout
	pContext->IASetInputLayout(pInputLayout.Get());


	//bind render target
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);


	//primitive topology for triangle list (3 vertices group)
	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = 640;
	vp.Height = 480;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);

	pContext->DrawIndexed((UINT)std::size(indices), 0u,0u);
}
void Renderer::EndFrame()
{
	pSwap->Present(1u, 0u);
}
