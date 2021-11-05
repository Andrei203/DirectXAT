#pragma once
#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
	{
	public:
		VertexShader(Renderer& Rnd, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);
		void Bind(Renderer& Rnd) override;
	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};


