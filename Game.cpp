#include "Game.h"
//#include "pauseMenu.h"
//#include "mainMenu.h"

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
			{
				running = true;
				
				mainM = &m;
				pauseM = &p;
				mainM->loadTextures(renderer);
				pauseM->loadTextures(renderer);
			}
		}
	}
	else 
	{
		SDL_Log("Initialization error. SDL_Error: %s", SDL_GetError());
	}
}

void Game::eventHandler() 
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) 
	{
		running = false;
	}
	else if ((event.type == SDL_KEYDOWN) && (event.key.repeat == 0) && (event.key.keysym.sym == SDLK_ESCAPE) && (mainM->isIn() == false)) 
	{
		pauseM->setIn(true);
		SDL_Log("bubun hah\n");
	}


}

void Game::clear() 
{
	delete lvl;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void Game::update() 
{	
	if(mainM->isIn())
	{
		switch (mainM->buttonPressed(&event))
		{
		case 1:
			delete lvl;
			lvl = new level(renderer, 1);
			break;
		case 2:
			delete lvl;
			lvl = new level(renderer, 2);
			break;
		case 3:
			delete lvl;
			lvl = new level(renderer, 3);
			break;
		case 4:
			running = false;
			break;
		default:
			break;
		}
	}
	else if(pauseM->isIn())
	{
		switch (pauseM->buttonPressed(&event))
		{
		case 0:
			pauseM->setIn(false);
			break;
		case 1:
			pauseM->setIn(false);
			mainM->setIn(true);
			break;
		default:
			break;
		}
	}
	else 
	{
		lvl->lvlEventHandler(&event, renderer);
	}
}

void Game::render() 
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	if (mainM->isIn()) 
	{
		mainM->draw(renderer);
	}
	else if(pauseM->isIn())
	{
		pauseM->draw(renderer);
	}
	else 
	{
		lvl->drawLvlFloor(renderer);
		lvl->drawLvlObjs(renderer);
	}

	SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::getRenderer()
{
	return renderer;
}