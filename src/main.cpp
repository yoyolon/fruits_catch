#include "Game.h"
#include <iostream>

int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	std::cout << game.Get_Score();
	game.Shutdown();
	return 0;
}