#include "BallRenderer.h"

BallRenderer::BallRenderer()
{
}

void BallRenderer::render(const Ball& ball, SDL_Renderer* renderer) const
{
	SDL_Rect ballRect{
		static_cast<int>(ball.getPosition().x - thickness / 2),
		static_cast<int>(ball.getPosition().y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ballRect);
}
