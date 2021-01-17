#pragma once
#include <iostream>
#include <SDL.h>
#include "Ball.h"

class BallRenderer
{
public:
	BallRenderer(class Game* game);

	void render(class Ball* ball) const;
private:
	void draw_circle(class Ball* ball) const;

	class Game* mGame;
};

