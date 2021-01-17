#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <SDL.h>
#include "Component.h"
#include "Actor.h"
#include <iostream>

using namespace std;

class Game
{
public:
	Game(const string& titleWindow);
	virtual ~Game();

	// Initialize the game
	bool initialize();

	// Runs the game loop until the game is over
	void runLoop();

	// Shutdown the game
	void shutdown();

	// Add actor
	void addActor(class Actor* actor);

	// Remove actor
	void removeActor(class Actor* actor);

	SDL_Renderer* getRenderer() const;

	Actor* getPaddle();
	void setPaddle(class Actor* paddle);
protected:
	virtual void processInput();
	virtual void update();
	virtual void render();

private:
	void renderActors();

	void waitFor(int mills) const;

	// Title that appears into window
	string mTitleWindow;

	unordered_set<class Component*> mComponents;

	// Actors of game
	vector<class Actor*> mActors;

	// Actors that were added when game was updating
	vector<class Actor*> mPendingActors;

	// Flag that indicates game is updating
	bool mUpdatingActors;

	// Window create by SDL
	SDL_Window* mWindow;

	// Game should continue to run
	bool mIsRunning;

	// Renderer
	SDL_Renderer* mRenderer;

	Uint32 mTicksCount;

	// Not good, but for actual version of game is better hold a reference to paddle because 
	// Ball updateActor method need for check collision
	class Actor* mPaddle;
};

