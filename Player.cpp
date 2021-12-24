#include "Player.h"
#include "textureManager.h"
#include "Game.h"

bool Player::inputHandler(SDL_Event* e)
{
	bool shoot = false;

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
		case SDLK_SPACE:
			shoot = true;
			SDL_Log("bang!\n");
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

	//set next animation frame
	if (yVelocity != 0 || xVelocity != 0) 
	{
		if (animID == 9)
			animID = 0;
		else
			animID++;
	}

	return shoot;
}

void Player::objsCollision(SDL_Rect r)
{
	//static game objects collision detection (is verifying for every side os the static object)
	if ((xVelocity > 0) && (shape.x + shape.h >= r.x - 1) && (shape.x + shape.h < r.x + 3) && (shape.y >= r.y - shape.w) && (shape.y <= r.y + r.h))
		xVelocity = 0;
	if ((xVelocity < 0) && (shape.x <= r.x + r.w + 1) && (shape.x > r.x + r.w - 3) && (shape.y >= r.y - shape.w) && (shape.y <= r.y + r.h))
		xVelocity = 0;
	if ((yVelocity > 0) && (shape.y + shape.h >= r.y - 1) && (shape.y < r.y + 3) && (shape.x >= r.x - shape.w) && (shape.x <= r.x + r.w))
		yVelocity = 0;
	if ((yVelocity < 0) && (shape.y <= r.y + r.h + 1) && (shape.y > r.y + r.h - 3) && (shape.x >= r.x - shape.w) && (shape.x <= r.x + r.w))
		yVelocity = 0;
}

void Player::mapCollision()
{
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

int Player::getViewDir()
{
	return viewDirection;
}

SDL_Rect Player::getHitBox()
{
	return shape;
}
