#include "Game.h"

Game::Game()
{
}

bool Game::initialize()
{
	// Init Video
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create a Window
	mWindow = SDL_CreateWindow(
		"Pong Game",
		100,
		100,
		1024,
		768,
		0
	);
	if (!mWindow) {
		SDL_Log("Failed to create a window: %s", SDL_GetError());
		cout << "ERRO " << SDL_GetError() << endl;
		return false;
	}

	mIsRunning = true;

	return true;
}

void Game::runLoop()
{
	while (mIsRunning) {
		processInput();
		updateGame();
		renderGame();
	}
}

void Game::shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::processInput()
{
}

void Game::updateGame()
{
}

void Game::renderGame()
{
}
