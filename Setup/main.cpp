#include <SDL.h>
#include <SDL_image.h>   
#include <iostream>
#include <string>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include <list>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* texture;
SDL_Rect sourceRectangle;
SDL_Rect destinationRectangle;

int main(int argc, char **argv){

	//initiate SDL with the subsystems you want to use ie SDL_INIT_VIDEO
	//we're initialising all of them (sound, input, video, etc)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "SDL Fail initialized!!!\n";
		return -1; //failed, don't continue rest of main code
	}
	else
	{
		cout << "SDL initialized success!!!\n";
	}

	//NEED TO INIT SDL_Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		std::system("pause");
		return -1;
	}

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	window = SDL_CreateWindow("666", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN /* | SDL_WINDOW_FULLSCREEN*/);

	if (window != NULL){
		cout << "Window created!"<< endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	//create renderer to help draw stuff to the screen
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL){
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer failed!" << endl;
		return -1;
	}

	//LOAD UP WHATEVER ASSETS HERE AFTER INIT

	//to load up an image, first load it up as a surface
	SDL_Surface* knightSurface = SDL_LoadBMP("assets/knight.bmp");
	//then convert to texture
	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
	//Dont need the surface anymore, free the memory up
	SDL_FreeSurface(knightSurface);

	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(knightTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
	cout << "Texture size is: " << sourceRectangle.w << "x" << sourceRectangle.h << endl;

	sourceRectangle.x = 100;
	sourceRectangle.y = 0;
	sourceRectangle.w = 100;
	sourceRectangle.h = 100;
	destinationRectangle.x = 100;
	destinationRectangle.y = 50;
	destinationRectangle.w = sourceRectangle.w*2; //copy the width of our texture
	destinationRectangle.h = sourceRectangle.h*2; //copy the height of out texture

	//RUN TEXTURE
	SDL_Texture* runSpriteSheet = IMG_LoadTexture(renderer, "assets/run.png");
	//this time, lets make a source rectangle copying just 1 frame in size at a time
	SDL_Rect runClipRect = { 0, 0, 32, 32 }; //x:0, y:0, w:32, h:32
	SDL_Rect runDestRect = { 0, 0, 128, 128 }; //x y, get image to bottom right of screen. w/h match clip/frame size

	SDL_Surface* runSurface = IMG_Load("assets/run.png");

	//param: surface, 1/0 t oset or unset color, rgb value to make colour key. mapRGB just does its best to find closest match to a surfaces pixel format e.g 8bit, 16bit, 32bit and what colours are in that set
	SDL_SetColorKey(runSurface, 1, SDL_MapRGB(runSurface->format, 128, 128, 255));

	//now convert to texture
	SDL_Texture* runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);
	//free the surface :O
	SDL_FreeSurface(runSurface);

	//Animation Objects
	Animation anim1(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.2); //0.2 = 200 milliseconds per frame of animation
	Animation anim2(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.8);
	Animation anim3(runSpriteSheetWithNoBG, renderer, 4, 32, 32, 0.05); //50ms per frame

	//setup time stuff
	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	//list of games entities
	list<Entity*> entities;
	//build hero
	Hero* hero = new Hero();
	hero->setAnimation(&anim3);
	hero->setRenderer(renderer);
	hero->setXY(30, 200);
	//add our hero to the list
	entities.push_back(hero);

	bool loop = true;
	while (loop){

		//difference is current time running minus the last update time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert into delta deltaTime (decimal)
		float DT = timeDiff / 1000.0;
		//now update lastUpdate to the current time so the next loop calculates correctly
		lastUpdate = SDL_GetTicks();

		//set drawing color for the renderer, numbers are: RGBA(alpha, transparency). All values between 0-255
		SDL_SetRenderDrawColor(renderer, 255, 0, 168, 255);
		//Clear screen with current draw color
		SDL_RenderClear(renderer);
		//TODO draw stuff to renderer here, like games images, colors, ui whatever
		//Set drawing color to BABY blue
		SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255);
		//Make a SDK_REct, to describe a rectangle x,y,w,h
		SDL_Rect rect = { 100, 50, 300, 240 };

		//Render rectangle to screen (renderer and a rectabgle for positioning)
		SDL_RenderFillRect(renderer, &rect);

		//DRAW OUR 2D IMAGES HERE
		SDL_RenderCopy(renderer, knightTexture, &sourceRectangle, &destinationRectangle);

		//lets do animation stuff here:
		int const runNumOfFrames = 4;
		runClipRect.x = runClipRect.w*int((SDL_GetTicks() / 100) % runNumOfFrames);
		//draw current frame to screen
		//SDL_RenderCopy(renderer, runSpriteSheet, &runClipRect, &runDestRect);

		//update animations
		/*anim1.update(DT);
		anim2.update(DT);
		anim3.update(DT);
		//draw from animations
		anim1.draw(50, 50);
		anim2.draw(50, 100, 4.0f); //4.0f is scale, stretch by 4x
		anim3.draw(50, 250, true); //flip image horizontally
		*/

		//loop through and update and draw all entities
		for (list<Entity*>::iterator eIt = entities.begin(); eIt != entities.end(); eIt++){
			(*eIt)->update(DT);
			(*eIt)->draw();
		}

		//then
		//get renderer to output to the window
		SDL_RenderPresent(renderer);
		//SDL_Delay pauses game for x many milliseconds
		//SDL_Delay(5000);//5000ms = 5 seconds

		if (SDL_GetTicks() > 5000){
			loop = false;
		}
	}

	//clean up any game objects
	delete hero;

	//cleanup renderer and window properly (aka cleanup dynamic memory)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down subsystems and cleanup any setup it did earlier in sdl_init
	SDL_Quit();

	system("pause");

	return 0;
}