#include "Paddle.h"

Paddle::Paddle(): mPaddleDir(0)
{
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
}

Vector2 Paddle::getPosition() const
{
	return mPaddlePos;
}

void Paddle::processInput(const Uint8* state)
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

void Paddle::update(float deltaTime)
{
	// Update paddle position based on direction
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime; // 300 pixel/sec

		// Make sure paddle doesn't move off screen
		if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness)) {
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
}

void Paddle::render(SDL_Renderer* renderer)
{
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(renderer, &paddle);
}

