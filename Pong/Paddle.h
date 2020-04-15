#pragma once

#include <SDL.h>
#include "Common.h"

class Paddle
{
public:
	Paddle();

	Vector2 getPosition() const;

	void processInput(const Uint8* state);

	void update(float deltaTime);

	void render(SDL_Renderer* renderer);
private:
	Vector2 mPaddlePos;

	int mPaddleDir;
};

