#include "Player.h"
#include "textureManager.h"
#include "Game.h"

bool Player::inputHandler(SDL_Event* e)
{
	bool shoot = false;

	if (e->type == SDL_KEYDOWN && e->key.repeat == 0) // key pressed
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
			if (SDL_GetTicks() - lastShootTime >= 3500) 
			{
				shoot = true;
				lastShootTime = SDL_GetTicks();
			}
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP && e->key.repeat == 0) // key released
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

	if (shoot == false) //that is for shooting if button was in pressed state wehen gun reloaded (using SDL keyboard state)
	{
		const Uint8* keyStates = SDL_GetKeyboardState(NULL);
		if (keyStates[SDL_SCANCODE_SPACE] && (SDL_GetTicks() - lastShootTime >= 3500))
		{
			shoot = true;
			lastShootTime = SDL_GetTicks();
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

bool Player::objsCollision(SDL_Rect r)
{
	//static game objects collision detection 
	if ((xVelocity > 0) && (shape.x + shape.h >= r.x - 2) && (shape.x + shape.h < r.x + 1) && (shape.y >= r.y - shape.w) && (shape.y <= r.y + r.h) && (viewDirection == 90))
		xVelocity = 0;
	if ((xVelocity < 0) && (shape.x <= r.x + r.w + 2) && (shape.x > r.x + r.w - 1) && (shape.y >= r.y - shape.w) && (shape.y <= r.y + r.h) && (viewDirection == 270))
		xVelocity = 0;
	if ((yVelocity > 0) && (shape.y + shape.h >= r.y - 2) && (shape.y < r.y + 1) && (shape.x >= r.x - shape.w) && (shape.x <= r.x + r.w) && (viewDirection == 180))
		yVelocity = 0;
	if ((yVelocity < 0) && (shape.y <= r.y + r.h + 2) && (shape.y > r.y + r.h - 1) && (shape.x >= r.x - shape.w) && (shape.x <= r.x + r.w) && (viewDirection == 0))
		yVelocity = 0;

	if (HP <= 0)
		return true;
	return false;
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

	if(HP >= 0 && HP < 5)
	{
		SDL_Rect r = { 0, 620, 70,30 };
		textureManager::drawTexture(HPtextures[HP], NULL, rend, &r, 0);
	}
}

void Player::loadTextures(SDL_Renderer* rend)
{
	texturesArray = new SDL_Texture * [2];
	texturesArray[0] = textureManager::loadTexture("assets/png/1.png", rend);
	texturesArray[1] = textureManager::loadTexture("assets/png/2.png", rend);

	HPtextures = new SDL_Texture * [5];
	HPtextures[0] = textureManager::loadTexture("assets/png/hp0.png", rend);
	HPtextures[1] = textureManager::loadTexture("assets/png/hp1.png", rend);
	HPtextures[2] = textureManager::loadTexture("assets/png/hp2.png", rend);
	HPtextures[3] = textureManager::loadTexture("assets/png/hp3.png", rend);
	HPtextures[4] = textureManager::loadTexture("assets/png/hp4.png", rend);
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

void Player::getDmg(int dmg)
{
	HP = HP - dmg;
}
