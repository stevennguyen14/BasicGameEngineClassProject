#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::setRenderer(SDL_Renderer* renderer){

	this->renderer = renderer;
}

void Entity::setXY(float x, float y){

	this->x = x;
	this->y = y;
}

float Entity::getX(){
	return x;
}

float Entity::getY(){
	return y;
}

void Entity::update(float dt){
	//do nothing, unless subclasses do something with it
}

void Entity::draw(){
	//also do nothing for now
}
