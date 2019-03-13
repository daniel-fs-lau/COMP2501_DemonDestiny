#include "Boulder.h"



Boulder::Boulder()
{
}

Boulder::Boulder(float x, float y, float dx, float dy, int st, float sp, float tx, float ty) :Projectile(x, y, dx, dy, st, sp,tx,ty) {
	id = "boulder";
}


Boulder::~Boulder()
{
}

void Boulder::update(float dt) {
	float dx = (target.x) - pos.x;
	float dy =  (target.y) - pos.y;
	float dist = sqrt((dx*dx) + (dy*dy));
	pos.x += (dx / dist)*speed;
	pos.y += (dy / dist)*speed;
}