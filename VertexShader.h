#pragma once
#include "Bindable.h"
#include <string>

class VertexShader : public Bindable
	{
	public:
		VertexShader(Renderer& Rnd, const std::wstring& path);
		void Bind(Renderer& Rnd) noexcept override;
		ID3DBlob* GetBytecode() const noexcept;
	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	};


