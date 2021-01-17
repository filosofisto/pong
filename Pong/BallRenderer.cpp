#include "BallRenderer.h"

BallRenderer::BallRenderer(class Game* game)
	: mGame(game)
{
}

void BallRenderer::render(class Ball* ball) const
{
	/*cout << "Rendering ball ratio: " << ball->getRadius() 
		 << ", (" << ball->getPosition().x << ", " << ball->getPosition().y << ")"
		 << endl;*/
	draw_circle(ball);
	/*SDL_Rect ballRect{
		static_cast<int>(ball.getPosition().x - thickness / 2),
		static_cast<int>(ball.getPosition().y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ballRect);*/
}

void BallRenderer::draw_circle(class Ball* ball) const
{
	int radius = ball->getRadius();
	SDL_Renderer* renderer = mGame->getRenderer();
	Vector2 position = ball->getPosition();

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
					static_cast<int>(position.x) + dx, 
					static_cast<int>(position.y) + dy);
			}
		}
	}
}
