#pragma once

#include "Common.h"
#include "Paddle.h"

class Ball
{
public:
	Ball();

	void update(float deltaTime, const Paddle& paddle);

	void setPosition(float xPos, float yPos);

	void setVelocity(float xVel, float yVel);

	void setRadius(int radius);

	Vector2 getPosition() const;

	int getRadius() const;
private:
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
	// Radius of ball
	int radius;
};

