#include "Wall.h"

Wall::Wall(class Game* game, class WallRenderer* renderer, int x, int y, int width, int height)
	:Actor(game)
	,mRenderer(renderer)
	,mX(x)
	,mY(y)
	,mWidth(width)
	,mHeight(height)
{
}

Wall::~Wall()
{
}

void Wall::renderActor()
{
	mRenderer->render(this);
}

int Wall::getX() const
{
	return mX;
}

int Wall::getY() const
{
	return mY;
}

int Wall::getWidth() const
{
	return mWidth;
}

int Wall::getHeight() const
{
	return mHeight;
}
