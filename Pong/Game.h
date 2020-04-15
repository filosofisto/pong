#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

struct Vector2
{
	float x;
	float y;
};

const int thickness = 15;
const int paddleH = 100;

class Game
{
public:
	Game();

	// Initialize the game
	bool initialize();

	// Runs the game loop until the game is over
	void runLoop();

	// Shutdown the game
	void shutdown();

private:
	// Helper functions for the game loop
	void processInput();
	void updateGame();
	void renderGame();

	// Window create by SDL
	SDL_Window* mWindow;

	// Game should continue to run
	bool mIsRunning;

	// Renderer
	SDL_Renderer* mRenderer;

	// Position of paddle
	Vector2 mPaddlePos;
	// Position of ball
	Vector2 mBallPos;
	// Velocity of ball
	Vector2 mBallVel;
	SDL_Rect wall;
	SDL_Rect ball;
	Uint32 mTicksCount;
	int mPaddleDir;
};

