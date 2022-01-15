#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "level.h"
#include "mainMenu.h"
#include "pauseMenu.h"


class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;

	level* lvl = NULL;
	SDL_Event event;
	
	menu* pauseM;
	menu* mainM;
	mainMenu m;
	pauseMenu p;

public:
	static const int screenWidth;
	static const int screenHeight;

	Game() 
	{
		window = NULL;
		renderer = NULL;
		running = false;
		
		lvl = NULL;

		pauseM = NULL;
		mainM = NULL;
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
