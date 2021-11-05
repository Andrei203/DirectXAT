#pragma once
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Renderer& Rnd, const std::vector<unsigned short>& indices);
	void Bind(Renderer& Rnd) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};
