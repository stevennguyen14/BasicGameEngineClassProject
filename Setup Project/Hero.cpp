#include "Hero.h"


Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::setAnimation(Animation* animation){
	this->animation = animation;
}

//overriding
void Hero::update(float dt){
	if (faceRight)
	{
		x += dt*800;
	}
	else
	{
		x -= dt*800;
	}

	if (x >= 640)
		faceRight = false;
	if (x <= 0)
		faceRight = true;

	//update animations too
	animation->update(dt);
}
void Hero::draw(){
	if (animation != NULL){
		if (faceRight)
			animation->draw(x, y);
		else
			animation->draw(x, y, true);
	}
}