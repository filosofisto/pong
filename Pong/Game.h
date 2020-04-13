#pragma once

#include <iostream>
#include <SDL.h>

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

	// Window create by SDL
	SDL_Window* mWindow;

	// Game should continue to run
	bool mIsRunning;
};
