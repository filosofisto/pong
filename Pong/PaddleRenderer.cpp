#include "PaddleRenderer.h"

PaddleRenderer::PaddleRenderer(class Game* game)
	:mGame(game)
{
}

void PaddleRenderer::render(class Paddle* paddle) const
{
	Vector2 position = paddle->getPosition();
	cout << "Rendering Paddle into position(" << position.x << ", " << position.y << ")" << endl;

	SDL_Rect paddleRect{
		static_cast<int>(position.x),
		static_cast<int>(position.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mGame->getRenderer(), &paddleRect);
}
