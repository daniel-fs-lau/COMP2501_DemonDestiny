#include "Enemy.h"

#include <sstream>
#include <iostream>
#include <iostream>
#include <fstream>


Enemy::Enemy():Updateable()
{
	Weapon *w1 = new Weapon("Leg Bone Wand", 20, 30, "Weapon", 0, 0);
	items.push_back(w1);
	Weapon *w2 = new Weapon("Arm Bone Wand", 10, 12, "Weapon", 0, 0);
	items.push_back(w2);
	id = "enemy";
	speed = 1;
}


Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime) {
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;
	float dist = sqrt((dx*dx) + (dy*dy));
	pos.x += (dx / dist)*speed;
	pos.y += (dy / dist)*speed;
	//std::cout << target.x << std::endl;
}


void Enemy::shoot() {
}

std::vector<Projectile*>& Enemy::getProjectiles() { return projectiles; }
std::vector<Item*>& Enemy::getItems() { return items; }