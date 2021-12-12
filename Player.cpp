#include "Player.h"
#include "textureManager.h"
#include "Game.h"

void Player::eventHandler(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_UP:
			if (yVelocity > -velocity) 
			{
				yVelocity -= velocity;
				xVelocity = 0;
				viewDirection = 0;
			}
			break;
		case SDLK_DOWN:
			if (yVelocity < velocity) 
			{
				yVelocity += velocity;
				xVelocity = 0;
				viewDirection = 180;
			}
			break;
		case SDLK_LEFT:
			if (xVelocity > -velocity) 
			{
				xVelocity -= velocity;
				yVelocity = 0;
				viewDirection = 270;
			}
			break;
		case SDLK_RIGHT:
			if (xVelocity < velocity) 
			{
				xVelocity += velocity;
				yVelocity = 0;
				viewDirection = 90;
			}
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_UP:
			if(yVelocity < 0)
				yVelocity += velocity;
			break;
		case SDLK_DOWN:
			if(yVelocity > 0)
				yVelocity -= velocity;
			break;
		case SDLK_LEFT:
			if(xVelocity < 0)
				xVelocity += velocity;
			break;
		case SDLK_RIGHT:
			if(xVelocity > 0)
				xVelocity -= velocity;
			break;
		default:
			break;
		}
	}

	if (yVelocity != 0 || xVelocity != 0) 
	{
		if (animID == 9)
			animID = 0;
		else
			animID++;
	}
}

void Player::collisionHandler(SDL_Event* e) 
{
	//map border collision detect
	if ((shape.y == 1 && yVelocity < 0) || (shape.y == Game::screenHeight - 1 - shape.h && yVelocity > 0))
		yVelocity = 0;
	if ((shape.x == 1 && xVelocity < 0) || (shape.x == Game::screenWidth - 1 - shape.w && xVelocity > 0))
		xVelocity = 0;
		
}

void Player::draw(SDL_Renderer* rend) 
{
	textureManager::drawTexture(texturesArray[animID/5], NULL, rend, &shape, viewDirection);
}

void Player::loadPlayerTextures(SDL_Renderer* rend)
{
	texturesArray = new SDL_Texture * [2];
	texturesArray[0] = textureManager::loadTexture("assets/png/1.png", rend);
	texturesArray[1] = textureManager::loadTexture("assets/png/2.png", rend);
}

void Player::move() 
{
	shape.y += yVelocity;
	shape.x += xVelocity;
}