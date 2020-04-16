#include "BallRenderer.h"

BallRenderer::BallRenderer()
{
}

void BallRenderer::render(const Ball& ball, SDL_Renderer* renderer) const
{
	draw_circle(ball, renderer);
	/*SDL_Rect ballRect{
		static_cast<int>(ball.getPosition().x - thickness / 2),
		static_cast<int>(ball.getPosition().y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ballRect);*/
}

void BallRenderer::draw_circle(const Ball& ball, SDL_Renderer* renderer) const
{
	int radius = ball.getRadius();

	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(
					renderer, 
					static_cast<int>(ball.getPosition().x) + dx, 
					static_cast<int>(ball.getPosition().y) + dy);
			}
		}
	}
}
