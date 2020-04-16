#include "PaddleRenderer.h"

PaddleRenderer::PaddleRenderer()
{
}

void PaddleRenderer::render(const Paddle& paddle, SDL_Renderer* renderer) const
{
	SDL_Rect paddleRect{
		static_cast<int>(paddle.getPosition().x),
		static_cast<int>(paddle.getPosition().y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(renderer, &paddleRect);
}
