#pragma once
#include "Projectile.h"
class BigBullet :public Projectile
{
public:
	BigBullet();
	BigBullet(float x, float y, float dx, float dy, int st, float sp, float tx, float ty);
	~BigBullet();
	void update(float);
};

