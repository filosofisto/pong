#include "Game.h"

Game::Game(): 
	mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mIsRunning(true)
{
	ball.setPosition(width / 2.0f, height / 2.0f);
	ball.setVelocity(xBallInitVelocity, yBallInitVelocity);
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
		xWindow,
		yWindow,
		wWindow,
		hWindow,
		0
	);
	if (!mWindow) {
		SDL_Log("Failed to create a window: %s", SDL_GetError());
		return false;
	}

	// Renderer
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1, // which graphics driver to use (multiple monitors, but only one -1)
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Acelerate and VSync (adaptative refresh)
	);

	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
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
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::processInput()
{
	SDL_Event event;

	//While there are still events in the queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}

		// Get state of keyboard
		const Uint8* state = SDL_GetKeyboardState(NULL);
		// If escape is pressed, also end loop
		if (state[SDL_SCANCODE_ESCAPE]) {
			mIsRunning = false;
		} 

		// Update direction of paddle if W/S keys pressed
		paddle.processInput(state);
	}
}

void Game::updateGame()
{
	// Wait until 16ms has elapsed since last frame
	waitFor(16);

	// Delta time is the difference in ticks from last frame (converted in seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	paddle.update(deltaTime);

	// Update ball position
	ball.update(deltaTime, paddle);

	// Did the ball go off the screen? (if so, end game)
	if (ball.getPosition().x <= 0.0f)
	{
		mIsRunning = false;
	}
}

void Game::renderGame()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw paddle
	paddleRenderer.render(paddle, mRenderer);
	
	// Draw ball
	ballRenderer.render(ball, mRenderer);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::waitFor(int mills) const
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + mills));
}
