#pragma once

#include <SDL.h>
#include "Ball.h"

class BallRenderer
{
public:
	BallRenderer();

	void render(const Ball& ball, SDL_Renderer* renderer) const;

private:
	void draw_circle(const Ball& ball, SDL_Renderer* renderer) const;
};

