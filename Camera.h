#pragma once
#include "Drawable.h"

class Camera : public Drawable
{
public:
	Camera(Renderer& Rnd);
	void Draw(Renderer& Rnd);
};

