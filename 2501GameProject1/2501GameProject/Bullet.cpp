#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(float x, float y, float dx, float dy, int st, float sp, float tx, float ty) :Projectile(x, y, dx, dy, st, sp, tx, ty) {
	id = "bullet";
}


Bullet::~Bullet()
{
}

void Bullet::update(float dt) {
	if (!FIRED) {
		dx = (target.x) - pos.x;
		dy = (target.y) - pos.y;
		dist = sqrt((dx*dx) + (dy*dy));
		FIRED = true;
	}
	pos.x += (dx / dist)*speed;
	pos.y += (dy / dist)*speed;
}