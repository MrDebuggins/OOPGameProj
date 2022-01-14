#pragma once
#include "menu.h"
class mainMenu : public menu
{
private:
	bool active[4] = { false,false,false,false };
	int time = 0;
public:
	void loadTextures(SDL_Renderer* rend);
	int eventHandler(SDL_Event* e, SDL_Renderer* rend);
	void draw(SDL_Renderer* rend);
	int buttonPressed(SDL_Event* e);
	bool isIn() { return in; }

	//mainMenu() 
	//{
	//	buttonHitBoxes = NULL;
	//	buttonsTextures = NULL;
	//}
};

