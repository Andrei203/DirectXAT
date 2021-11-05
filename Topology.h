#pragma once
#include "Bindable.h"
class Topology : public Bindable
{
public:
	Topology( Renderer& Rnd,D3D11_PRIMITIVE_TOPOLOGY type );
	void Bind( Renderer& Rnd ) noexcept override;

protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};


