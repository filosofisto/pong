#pragma once
#include <iostream>
#include <SDL.h>
#include "Wall.h"

class WallRenderer
{
public:
	WallRenderer(class Game* game);
	virtual ~WallRenderer();

	void render(class Wall* wall) const;
private:
	class Game* mGame;
};

