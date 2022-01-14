#include "Game.h"

const int Game::screenWidth = 1200;
const int Game::screenHeight = 650;

void Game::initGame(const char title[], int pos_x, int pos_y, SDL_WindowFlags windowFlags) 
{
	if ((SDL_Init(SDL_INIT_EVERYTHING) == 0) && (IMG_Init(IMG_INIT_PNG)))
	{
		window = SDL_CreateWindow(title, pos_x, pos_y, screenWidth, screenHeight, NULL);
		if (window == NULL)
		{
			SDL_Log("Windows creation error. SDL_Error: %s", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) 
			{
				SDL_Log("Render creation error. SDL_Error: %s", SDL_GetError());
			}
			else
				running = true;
		}
	}
	else 
	{
		SDL_Log("Initialization error. SDL_Error: %s", SDL_GetError());
	}

	lvl1 = new level(renderer, 1);
}

void Game::eventHandler() 
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) 
	{
		running = false;
	}
}

void Game::clear() 
{
	//delete player;
	//player = NULL;
	delete lvl1;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void Game::update() 
{
	lvl1->lvlEventHandler(&event, renderer);
}

void Game::render() 
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	lvl1->drawLvlFloor(renderer);
	lvl1->drawLvlObjs(renderer);

	SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::getRenderer()
{
	return renderer;
}