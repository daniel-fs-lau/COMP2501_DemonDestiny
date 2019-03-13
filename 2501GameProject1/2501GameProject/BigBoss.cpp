#include "BigBoss.h"

BigBoss::BigBoss()
{
	items.pop_back();
	items.pop_back();
	CreatureStone *c1 = new CreatureStone("Spider Egg", 1000, "Creature Egg", 0, 0);
	items.push_back(c1);
	pos.x = 400;
	pos.y = 400;
	id = "bigboss";
	health = 500;
	maxHealth = 500;
	shootTimer = 0;
}


BigBoss::~BigBoss()
{
}

void BigBoss::update(float) {
	if (shootTimer > 120) {
		shoot();
	}
	shootTimer++;
}

void BigBoss::shoot() {
	bool left;
	bool up;
	pos.x - target.x < 0 ? left = false : left = true;
	pos.y - target.y < 0 ? up = false : up = true;
	for (int i = 0; i < 5; i++) {
		Projectile* p = new Bullet(pos.x-30+i*10, pos.y-30+i*10, 0, 0, -1, 10, -30+i*10, -30+i*10);
		projectiles.push_back(p);
	}
	shootTimer = 0;
}

