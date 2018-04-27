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
	//face direction based on velocity.x value
	if (velocity.x > 0){
		faceRight = true;
	}
	if (velocity.x < 0){
		faceRight = false;
	}

	//use basic entity movement to move around
	updateMovement(dt);

	//update animations too
	animation->update(dt);
}
void Hero::draw(){
	if (animation != NULL){
		if (faceRight)
			animation->draw(pos.x, pos.y);
		else
			animation->draw(pos.x, pos.y, true);
	}
}