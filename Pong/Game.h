#pragma once

#include <iostream>
#include <SDL.h>
#include "Common.h"
#include "Ball.h"
#include "Paddle.h"
#include "BallRenderer.h"
#include "PaddleRenderer.h"

using namespace std;

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
	void waitFor(int mills) const;

	// Window create by SDL
	SDL_Window* mWindow;

	// Game should continue to run
	bool mIsRunning;

	// Renderer
	SDL_Renderer* mRenderer;

	// Paddle object
	Paddle paddle;

	// Paddle renderer
	PaddleRenderer paddleRenderer;
	
	// Ball object
	Ball ball;

	// Ball renderer
	BallRenderer ballRenderer;

	Uint32 mTicksCount;
};

