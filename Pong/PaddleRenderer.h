#pragma once
#include <iostream>
#include "Game.h"
#include "Paddle.h"

class PaddleRenderer
{
public:
	PaddleRenderer(class Game* game);

	void render(class Paddle* paddle) const;
private:
	class Game* mGame;
};

