#pragma once
#include "Bindable.h"
#include "Vertex.h"

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Renderer& Rnd, const std::vector<Vertex>& vertices);
	void Bind(Renderer& Rnd) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	UINT stride;
};