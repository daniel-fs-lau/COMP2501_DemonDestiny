#include "Tank.h"

Tank::Tank()
{
	id = "tank";
	charge = 5;
}


Tank::~Tank()
{
}

void Tank::update(float deltaTime) {
	if (state == FOLLOWING) {
		follow();
	}
	else if (state == RIDING) {
		shootTimer++;
		if (CHARGING&&charge<20) {
			charge += 0.1;
		}
	}
}

void Tank::shoot() {
	std::cout << "shot" << std::endl;
	if (shootTimer > 30) {
		Projectile* p = new BigBullet(pos.x, pos.y, 0, 0, -1, charge, -1, -1);
		projectiles.push_back(p);
		shootTimer = 0;
		charge = 5;
	}
}

void Tank::ride() {
	pos.x += round(sin(angle) * speed);
	pos.y -= round(cos(angle) * speed);
}

void Tank::follow() {
	dist = getDist();
	if (dist < speed) {
		//pos.x += round((dx)*speed);
		//pos.y += round((dy)*speed);
	}
	else {
		pos.x += round((dx / dist)*3);
		pos.y += round((dy / dist)*3);
	}
}


void Tank::setAngle(float a) { angle = a; }
float Tank::getAngle() { return angle; }
void Tank::setCharge(float c) { charge = c; }
float Tank::getCharge() { return charge; }
void Tank::setCharging(bool c) { CHARGING = c; }
bool Tank::getCharging() { return CHARGING; }