#include "Topology.h"

Topology::Topology(Renderer& Rnd, D3D11_PRIMITIVE_TOPOLOGY type):type(type)
{
}

void Topology::Bind(Renderer& Rnd)
{
	Rnd.GetContext()->IASetPrimitiveTopology(type);
}
