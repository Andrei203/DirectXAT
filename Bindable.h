#pragma once
#include "Renderer.h"
class Bindable
{
public:
	virtual void Bind(Renderer& renderer) = 0;
	virtual ~Bindable() = default;
};

