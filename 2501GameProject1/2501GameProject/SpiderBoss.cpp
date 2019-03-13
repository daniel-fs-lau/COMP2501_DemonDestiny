#include "SpiderBoss.h"

SpiderBoss::SpiderBoss()
{
	items.pop_back();
	items.pop_back();
	//Armour *a1 = new Armour("Apprentice Cloak", 20, 30, "Armour", 0, 0);
	CreatureStone *c1 = new CreatureStone("Tank Egg", 500, "Creature Egg", 0, 0);
	items.push_back(c1);

	speed = 1;
	pos.x = 1000;
	pos.y = 400-64*2;
	id = "spiderboss";
	health = 500;
	maxHealth = 500;
	shootTimer = 0;
	dir.x =1;
}


SpiderBoss::~SpiderBoss()
{
}

void SpiderBoss::update(float) {
	if (pos.x>=64*20||pos.x<64*6) {
		dir.x *= -1;
	}
	pos.x += dir.x;
	if (shootTimer > 120) {
		shoot();
	}
	shootTimer++;
}

void SpiderBoss::shoot() {
	bool left;
	bool up;
	pos.x - target.x < 0 ? left = false : left = true;
	pos.y - target.y < 0 ? up = false : up = true;
	Projectile* p = new Boulder(pos.x, pos.y, 0, 0, -1, 10,0,0);
	projectiles.push_back(p);
	shootTimer = 0;
}

