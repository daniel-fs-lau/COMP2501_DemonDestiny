#include "Ant.h"



Ant::Ant()
{
	id = "ant";
	speed = 2;
	size = 32;
}


Ant::~Ant()
{
}

void Ant::update(float deltaTime) {
	if (state == FOLLOWING) {
		follow();
		shootTimer++;
	}
	else if (state == RIDING) {

	}
}

void Ant::shoot() {

}

void Ant::ride() {
	pos.x += round(sin(angle) * speed);
	pos.y -= round(cos(angle) * speed);
}

void Ant::follow() {
	dist = getDist();
	if (dist < speed) {

	}
	else {
		pos.x += round((dx / dist)*speed);
		pos.y += round((dy / dist)*speed);
	}
}



void Ant::setAngle(float a) { angle = a; }
float Ant::getAngle() { return angle; }