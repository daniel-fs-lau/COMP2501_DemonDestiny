#include "BigBullet.h"



BigBullet::BigBullet()
{
}

BigBullet::BigBullet(float x, float y, float dx, float dy, int st, float sp, float tx, float ty) :Projectile(x, y, dx, dy, st, sp, tx, ty) {
	id = "bigbullet";
}


BigBullet::~BigBullet()
{
}

void BigBullet::update(float dt) {
	if (!FIRED) {
		dx = (target.x) - pos.x;
		dy = (target.y) - pos.y;
		dist = sqrt((dx*dx) + (dy*dy));
		FIRED = true;
	}
	pos.x += (dx / dist)*speed;
	pos.y += (dy / dist)*speed;
	if (speed > 0) {
		speed -= 0.1;
	}
	else {
		speed = 0;
	}
}