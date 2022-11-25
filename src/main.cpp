//--------------------------------------------------------------------------------------------------------------------
// fruits_catch
// yoyolon - November 2022
// 
// Development
// C++17
// Microsoft Visual Studio 2019
// 
// External Library
// SDL      : https://github.com/libsdl-org/SDL/tree/SDL2
// SDL_image: https://github.com/libsdl-org/SDL_image/
//
// Reference
// Sanjay Madhav(��), �g��M�v(�|��), �����t ��(�Ė�) "�Q�[���v���O���~���O C++" 2018.
// Sanjay Madhav "Game Programming in C++ Code" https://github.com/gameprogcpp/code 2017.
// 
// This software is based on "Game Programming in C++ Code"
// licensed under(https://github.com/gameprogcpp/code/blob/master/LICENSE).
//--------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	// �Q�[���I����
	if (game.Get_IsGameComplete()) {
		std::cout << "Congratulations! you have completed this game." << '\n';
	}
	else {
		std::cout << "You were failed to complete this game." << '\n';
	}
	std::cout << "Your Score: " << game.Get_Score() << '\n';
	game.Shutdown();
	return 0;
}