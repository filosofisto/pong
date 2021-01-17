#pragma once

#include <SDL.h>
#include "Common.h"
#include "Vector2.h"
#include "Actor.h"
#include "Game.h"
#include "PaddleRenderer.h"
#include <iostream>

class Paddle: public Actor
{
public:
	Paddle(class Game* game, class PaddleRenderer* paddleRenderer);

	void processInputActor(const Uint8* state);

	void updateActor(float deltaTime);

	void renderActor();
private:
	int mPaddleDir;
	class PaddleRenderer* mRenderer;
};

