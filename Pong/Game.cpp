#include "Game.h"

Game::Game(): 
	mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mIsRunning(true), 
	mPaddleDir(0)
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

	/*SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G
		255,	// B
		255		// A
	);
	SDL_RenderClear(mRenderer); // Clear back buffer to renderer color
	SDL_RenderPresent(mRenderer); // Swap the front and back buffers
	*/
	
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

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

		// Update paddle direction based on W/S keys
		mPaddleDir = 0;
		if (state[SDL_SCANCODE_W]) {
			mPaddleDir -= 1;
		}
		if (state[SDL_SCANCODE_S]) {
			mPaddleDir += 1;
		}
	}
}

void Game::updateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame (converted in seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Update paddle position based on direction
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime; // 300 pixel/sec

		// Make sure paddle doesn't move off screen
		if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness)) {
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
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
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}
