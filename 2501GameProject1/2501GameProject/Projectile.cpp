#include "Projectile.h"



Projectile::Projectile()
{
}

Projectile::Projectile(float x, float y, float dx, float dy, int st, float sp, float tx, float ty):Updateable(x,y,dx,dy,st,sp) {
	target.x = tx;
	target.y = ty;
	FIRED = false;
	dx, dy, dist = 0;
	state = -1;
	id = "projectile";
}

Projectile::~Projectile()
{
}
