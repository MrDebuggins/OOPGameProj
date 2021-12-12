#include <iostream>
//#include <fstream>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) 
{
	Game* gaym = new Game;
	gaym->initGame("gaym", 50, 50, SDL_WINDOW_SHOWN);


	while (gaym->isRunning()) 
	{
		gaym->eventHandler();
		gaym->update();
		gaym->render();
	}

	gaym->clear();

	return 0;
}
