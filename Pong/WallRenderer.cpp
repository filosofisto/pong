#include "WallRenderer.h"

WallRenderer::WallRenderer(class Game* game)
	:mGame(game)
{
}

WallRenderer::~WallRenderer()
{
}

void WallRenderer::render(class Wall* wall) const
{
	/*cout << "Rendering wall: (" << wall->getX() << ", " << wall->getY() 
		 << ", " << wall->getWidth() << ", " << wall->getHeight() << ")"
		 << endl;*/
	SDL_Rect rect{
		wall->getX(),		// Top left x
		wall->getY(),		// Top left y
		wall->getWidth(),	// Width
		wall->getHeight()	// Height
	};
	SDL_RenderFillRect(mGame->getRenderer(), &rect);
}
