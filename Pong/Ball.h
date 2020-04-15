#pragma once

#include "Common.h"
#include "Paddle.h"

class Ball
{
public:
	Ball();

	void update(float deltaTime, const Paddle& paddle);

	void render(SDL_Renderer* renderer);

	void setPosition(float xPos, float yPos);

	void setVelocity(float xVel, float yVel);

	Vector2 getPosition() const;
private:
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
};

