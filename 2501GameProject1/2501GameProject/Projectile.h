#pragma once
#include "Updateable.h"
class Projectile:public Updateable {
protected:
	float dx;
	float dy;
	float dist;
	bool FIRED;
public:
	Projectile();
	Projectile(float x, float y, float dx, float dy, int st, float sp,float tx,float ty );
	~Projectile();
	virtual void update(float) = 0;;
};

