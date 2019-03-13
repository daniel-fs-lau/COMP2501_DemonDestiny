#pragma once
#include "Projectile.h"
class Boulder:public Projectile
{
public:
	Boulder();
	Boulder(float x, float y, float dx, float dy, int st, float sp, float tx, float ty);
	~Boulder();
	void update(float);
};

