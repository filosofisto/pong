#pragma once

#include "Actor.h"
#include "WallRenderer.h"

class Wall : public Actor
{
public:
	Wall(class Game* game, class WallRenderer* renderer, int x, int y, int width, int height);
	virtual ~Wall();

	void renderActor();

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
private:
	int mX, mY, mWidth, mHeight;
	class WallRenderer* mRenderer;
};

