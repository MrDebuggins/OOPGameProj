#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	Game* game = new Game;
	game->initGame("Game", 50, 50, SDL_WINDOW_SHOWN);


	while (game->isRunning()) 
	{
		game->eventHandler();
		game->update();
		game->render();
	}

	game->clear();

	return 0;
}
