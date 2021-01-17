#include <iostream>

/*
	Important: Copy SDL2.dll to Windows\System folder
*/

#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Wall.h"
#include "Common.h"
#include "WallRenderer.h"
#include "PaddleRenderer.h"
#include "BallRenderer.h"
#include "Vector2.h"

using namespace std;

int main(int argc, char** argv)
{
	Game game("Pong Game");

	WallRenderer wallRenderer(&game);

	Wall topWall(&game, &wallRenderer, 0, 0, iwidth, thickness);
	Wall bottomWall(&game, &wallRenderer, 0, 768 - thickness, iwidth, thickness);
	Wall rightWall(&game, &wallRenderer, 1024 - thickness, 0, thickness, 1024);

	game.addActor(&topWall);
	game.addActor(&bottomWall);
	game.addActor(&rightWall);

	BallRenderer ballRenderer(&game);
	Ball ball(&game, &ballRenderer);
	ball.setPosition(Vector2(width / 2.0f, height / 2.0f));
	ball.setVelocity(xBallInitVelocity, yBallInitVelocity);
	ball.setRadius(7);

	PaddleRenderer paddleRenderer(&game);
	Paddle paddle(&game, &paddleRenderer);
	paddle.setPosition(Vector2(10.0f, 768.0f / 2.0f));

	game.addActor(&ball);
	game.addActor(&paddle);

	bool success = game.initialize();

	if (success) {
		game.runLoop();
	}
	
	game.shutdown();

	if (success) {
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}
}