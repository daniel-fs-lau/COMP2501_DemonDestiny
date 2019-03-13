#include "Slime.h"



Slime::Slime()
{
	speed = 1;
}


Slime::~Slime()
{
}


void Slime::ride() {
	pos.x += sin(angle) * speed;
	pos.y -= cos(angle) * speed;
}
