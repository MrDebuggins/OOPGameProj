#pragma once
#include <SDL.h>
#include <SDL_image.h>
//#include "Player.h"
#include "level.h"


class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;

	
	level* lvl1;
	SDL_Event event;
	//Player* player;
	

public:
	static const int screenWidth;
	static const int screenHeight;

	Game() 
	{
		window = NULL;
		renderer = NULL;
		running = false;
		//player = NULL;
	}

	bool isRunning() 
	{
		return running;
	}

	void initGame(const char title[], int pos_x, int pos_y, SDL_WindowFlags windowFlags);
	void eventHandler();
	void update();
	void render();
	void clear();
	SDL_Renderer* getRenderer();
};
