#include "Creature.h"



Creature::Creature()
{
	state = FOLLOWING;
	speed = 4;
}


Creature::~Creature()
{
}

float Creature::getDist() {
	dx = (target.x) - pos.x;
	dy = (target.y) - pos.y;
	dist = sqrt((dx*dx) + (dy*dy));
	return dist;
}

std::vector<Projectile*>& Creature::getProjectiles(){ return projectiles; }