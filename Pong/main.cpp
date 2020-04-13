#include <iostream>

/*
	Important: Copy SDL2.dll to Windows\System folder
*/

#include "Game.h"

using namespace std;

int main(int argc, char** argv)
{
	Game game;

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