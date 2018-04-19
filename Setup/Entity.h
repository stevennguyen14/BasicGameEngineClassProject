#pragma once
#include <SDL.h>

class Entity
{
protected:
	SDL_Renderer* renderer;
	float x, y;

public:
	Entity();
	~Entity();

	void setRenderer(SDL_Renderer* renderer);
	void setXY(float x, float y);
	float getX();
	float getY();

	virtual void update(float dt);
	virtual void draw();
};

