#pragma once
#include "Enemy.h"
#include "Bullet.h"

class BigBoss: public Enemy
{
	int shootTimer;
public:
	BigBoss();
	~BigBoss();
	void update(float);
	void shoot();
};

