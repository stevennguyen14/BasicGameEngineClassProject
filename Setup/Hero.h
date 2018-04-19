#pragma once
#include "Animation.h"
#include "Entity.h"
class Hero :
	public Entity
{
private:

	Animation* animation = NULL;
	bool faceRight = true;

public:
	Hero();
	~Hero();

	void setAnimation(Animation* animation);

	//overriding
	virtual void update(float dt);
	virtual void draw();
};

