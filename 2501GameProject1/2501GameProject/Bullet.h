#pragma once
#include "Projectile.h"
class Bullet :public Projectile
{
public:
	Bullet();
	Bullet(float x, float y, float dx, float dy, int st, float sp, float tx, float ty);
	~Bullet();
	void update(float);
};

