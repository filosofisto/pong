#pragma once

#include "Common.h"
#include "Paddle.h"
#include "Actor.h"
#include "Game.h"
#include "BallRenderer.h"

class Ball: public Actor
{
public:
	Ball(class Game* game, class BallRenderer* renderer);

	void updateActor(float deltaTime);

	void renderActor();

	void setVelocity(float xVel, float yVel);

	void setRadius(int radius);

	int getRadius() const;
private:
	// Velocity of ball
	Vector2 mBallVel;
	// Radius of ball
	int mRadius;

	class BallRenderer* mRenderer;
};

