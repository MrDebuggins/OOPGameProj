//#include <SDL.h>
//#include <SDL_image.h>
//#include <stdio.h>
//#include <string>
//
//bool init();
//bool load();
//void clear();
////SDL_Surface* loadSurface(std::string path);
//
//enum keySurfaces
//{
//	KEY_PRESS_SURFACE_DEFAULT,
//	KEY_PRESS_SURFACE_UP,
//	KEY_PRESS_SURFACE_DOWN,
//	KEY_PRESS_SURFACE_LEFT,
//	KEY_PRESS_SURFACE_RIGHT,
//	KEY_PRESS_SURFACE_TOTAL
//};
//
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 500;
//
//SDL_Window* winduv = NULL;
//SDL_Surface* screenSurface = NULL;
//SDL_Surface* image = NULL;
//
//SDL_Renderer* render = NULL;
//SDL_Texture* texture = NULL;
//
//SDL_Texture* keyPressTextures[KEY_PRESS_SURFACE_TOTAL];
//SDL_Texture* loadTexture(std::string path);
//
//
//int main( int argc, char* args[] )
//{
//	if (init()) 
//	{
//		//if (load()) 
//		//{
//			bool quit = false;
//			SDL_Event e;
//
//			while (!quit)
//			{
//				while (SDL_PollEvent(&e) != 0)
//				{
//				
//					if (e.type == SDL_QUIT)
//						quit = true;
//				}
//
//				SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
//				SDL_RenderClear(render);
//
//				SDL_Rect rect{ SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
//				SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
//				SDL_RenderFillRect(render, &rect);
//
//				SDL_Rect outline{ SCREEN_WIDTH / 6,SCREEN_HEIGHT / 6,SCREEN_WIDTH * 2 / 3,SCREEN_HEIGHT * 2 / 3 };
//				SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
//				SDL_RenderDrawRect(render, &outline);
//
//				SDL_RenderPresent(render);
//			}
//
//		//}
//	}
//
//	clear();
//	return 0;
//}
//
//bool init() 
//{
//	bool succes = true;
//	
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//	}
//	else
//	{
//		winduv = SDL_CreateWindow("gaim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (winduv == NULL)
//		{
//			printf("Could not create window!%s\n", SDL_GetError());
//			succes = false;
//		}
//		else 
//		{
//			render = SDL_CreateRenderer(winduv, -1, SDL_RENDERER_ACCELERATED);
//			if (render == NULL)
//			{
//				printf("Failed to create renderer. SDL_Error: %s\n", SDL_GetError());
//				succes = false;
//			}
//			else
//			{
//				SDL_SetRenderDrawColor(render, 0xff, 0xff, 0xff, 0xff);
//
//				int imgFlags = IMG_INIT_PNG;
//				if (!(IMG_Init(imgFlags) & imgFlags))
//				{
//					printf("Couldn't initialize SDL_Image. SDL_Error: %s", IMG_GetError());
//				}
//				else
//				{
//					screenSurface = SDL_GetWindowSurface(winduv);
//				}
//			}
//		}
//	}
//	return succes;
//}
//
//bool load() 
//{
//	bool succes = true;
//
//	keyPressTextures[KEY_PRESS_SURFACE_DEFAULT] = loadTexture("assets/png/def.png");
//	if (keyPressTextures[KEY_PRESS_SURFACE_DEFAULT] == NULL)
//	{
//		printf("Unable to load image: %s. SDL_Error: %s\n", "assets/press.bmp", SDL_GetError());
//		succes = false;
//	}
//
//	keyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("assets/png/d.png");
//	if (keyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL)
//	{
//		printf("Unable to load image: %s. SDL_Error: %s\n", "assets/down.bmp", SDL_GetError());
//		succes = false;
//	}
//
//	keyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("assets/png/l.png");
//	if (keyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL)
//	{
//		printf("Unable to load image: %s. SDL_Error: %s\n", "assets/left.bmp", SDL_GetError());
//		succes = false;
//	}
//
//	keyPressTextures[KEY_PRESS_SURFACE_RIGHT] = loadTexture("assets/png/r.png");
//	if (keyPressTextures == NULL)
//	{
//		printf("Unable to load image: %s. SDL_Error: %s\n", "assets/right.bmp", SDL_GetError());
//		succes = false;
//	}
//
//	keyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("assets/png/u.png");
//	if (keyPressTextures[KEY_PRESS_SURFACE_UP] == NULL)
//	{
//		printf("Unable to load image: %s. SDL_Error: %s\n", "assets/up.bmp", SDL_GetError());
//		succes = false;
//	}
//
//	return succes;
//}
//
//void clear() 
//{
//	SDL_DestroyWindow(winduv);
//	SDL_DestroyRenderer(render);
//	winduv = NULL;
//	render = NULL;
//
//	//SDL_FreeSurface(image);
//	//image = NULL;
//	//SDL_DestroyTexture(texture);
//	//texture = NULL;
//
//	//delete[] keyPressTextures;
//
//	IMG_Quit();
//	SDL_Quit();
//}
//
//SDL_Texture* loadTexture(std::string path) 
//{
//	SDL_Texture* newTexture = NULL;
//
//	//SDL_Surface* optimized = NULL;
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//
//	if (loadedSurface == NULL) 
//	{
//		printf("Unable to load bmp%s SDL_Error: %s\n", path.c_str(), SDL_GetError());
//	}
//	else 
//	{
//		newTexture = SDL_CreateTextureFromSurface(render, loadedSurface);
//		if (newTexture == NULL)
//			printf("Unable to create texture from image. SDL_Error: %s\n", SDL_GetError());
//	}
//
//	SDL_FreeSurface(loadedSurface);
//	return newTexture;
//}




#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene texture
LTexture gArrowTexture;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load arrow
	if (!gArrowTexture.loadFromFile("assets/png/arrow.png"))
	{
		printf("Failed to load arrow texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gArrowTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Angle of rotation
			double degrees = 0;

			//Flip type
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_a:
							degrees -= 5;
							break;

						case SDLK_d:
							degrees += 5;
							break;

						case SDLK_q:
							flipType = SDL_FLIP_HORIZONTAL;
							break;

						case SDLK_w:
							flipType = SDL_FLIP_NONE;
							break;

						case SDLK_e:
							flipType = SDL_FLIP_VERTICAL;
							break;
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render arrow
				gArrowTexture.render((SCREEN_WIDTH - gArrowTexture.getWidth()) / 2, (SCREEN_HEIGHT - gArrowTexture.getHeight()) / 2, NULL, degrees, NULL, flipType);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}