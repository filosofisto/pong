#include "Game.h"

Game::Game(const string& titleWindow):
	mTitleWindow(titleWindow),
	mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mIsRunning(true),
	mPendingActors(false),
	mUpdatingActors(false)
{
}

Game::~Game()
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
		mTitleWindow.c_str(),
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
		update();
		render();
	}
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
			break;
		}

		// Update direction of paddle if W/S keys pressed
		//paddle.processInput(state);
		for (vector<class Actor*>::const_iterator it = mActors.begin(); it != mActors.end(); ++it) {
			(*it)->processInputActor(state);
		}
	}
}

void Game::shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}


void Game::removeActor(Actor* actor)
{
	// Is it in pending actors?
	auto it = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (it != mPendingActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(it, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors
	it = find(mActors.begin(), mActors.end(), actor);
	if (it != mActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(it, mActors.end() - 1);
		mActors.pop_back();
	}
}

SDL_Renderer* Game::getRenderer() const
{
	return mRenderer;
}

Actor* Game::getPaddle()
{
	return mPaddle;
}

void Game::setPaddle(class Actor* paddle)
{
	mPaddle = paddle;
}

void Game::update()
{
	// Compute delta time
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

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto actor : mPendingActors) {
		mActors.emplace_back(actor);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->getState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which remove them from mActors
	for (auto actor : deadActors) {
		delete actor;
	}
}

void Game::render()
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

	renderActors();
	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::renderActors()
{
	for (vector<class Actor*>::const_iterator it = mActors.begin(); it != mActors.end(); ++it) {
		(*it)->render();
	}
}

void Game::waitFor(int mills) const
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + mills));
}
