#pragma once

#include "Paddle.h"

class PaddleRenderer
{
public:
	PaddleRenderer();

	void render(const Paddle& paddle, SDL_Renderer* renderer) const;
};

