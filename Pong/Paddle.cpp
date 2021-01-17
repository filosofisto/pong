#include "Paddle.h"

Paddle::Paddle(class Game* game, class PaddleRenderer* renderer)
	:Actor(game)
	,mRenderer(renderer)
	,mPaddleDir(0)
{
	game->setPaddle(this);

	Vector2 position = getPosition();
	position.x = 10.0f;
	position.y = 768.0f / 2.0f;
}


void Paddle::processInputActor(const Uint8* state)
{
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}
}

void Paddle::updateActor(float deltaTime)
{
	// Current vector position
	Vector2 position = getPosition();

	// Update paddle position based on direction
	if (mPaddleDir != 0) {
		float y = position.y + mPaddleDir * 300.0f * deltaTime; // 300 pixel/sec

		// Make sure paddle doesn't move off screen
		if (y < (paddleH / 2.0f + thickness)) {
			y = paddleH / 2.0f + thickness;
		}
		else if (y > (768.0f - paddleH / 2.0f - thickness)) {
			y = 768.0f - paddleH / 2.0f - thickness;
		}

		setPosition(Vector2(position.x, y));
	}

	//std::cout << "y = " << position.y << std::endl;
}

void Paddle::renderActor()
{
	mRenderer->render(this);
}


