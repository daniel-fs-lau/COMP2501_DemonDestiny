#include "Spider.h"



Spider::Spider()
{
	id = "spider";
}


Spider::~Spider()
{
}

void Spider::update(float deltaTime) {
	if (state == FOLLOWING) {
		follow();
		shootTimer++;
	}
	else if (state == RIDING) {

	}
}

void Spider::shoot() {
	if (shootTimer > 30) {
		Projectile* p = new Bullet(pos.x, pos.y, 0, 0, -1, 10, -1, -1);
		projectiles.push_back(p);
		shootTimer = 0;
	}
}

void Spider::ride() {
	pos.x += round(sin(angle) * speed);
	pos.y -= round(cos(angle) * speed);
}

void Spider::follow() {
	dist = getDist();
	if (dist < speed) {
		//pos.x += round((dx)*speed);
		//pos.y += round((dy)*speed);
	}
	else {
		pos.x += round((dx / dist)*speed);
		pos.y += round((dy / dist)*speed);
	}
}


void Spider::setAngle(float a) { angle = a; }
float Spider::getAngle() { return angle; }