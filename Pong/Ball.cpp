#include "Ball.h"

Ball::Ball(class Game* game, class BallRenderer* renderer)
	:Actor(game)
	,mRenderer(renderer)
	,mRadius(10)
{
}

void Ball::updateActor(float deltaTime)
{
	// Update ball position based on ball velocity
	Vector2 currentPosition = getPosition();
	float x = currentPosition.x + mBallVel.x * deltaTime;
	float y = currentPosition.y + mBallVel.y * deltaTime;
	setPosition(Vector2(x, y));

	Actor* paddle = mGame->getPaddle();
	
	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = paddle->getPosition().y - y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		x <= 25.0f && x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball collide with the right wall?
	else if (x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

	if (x < 0) {
		mGame->setRunning(false);
	}
}

void Ball::renderActor()
{
	mRenderer->render(this);
}

void Ball::setVelocity(float xVel, float yVel)
{
	mBallVel.x = xVel;
	mBallVel.y = yVel;
}

void Ball::setRadius(int radius)
{
	this->mRadius = radius;
}

int Ball::getRadius() const
{
	return mRadius;
}
