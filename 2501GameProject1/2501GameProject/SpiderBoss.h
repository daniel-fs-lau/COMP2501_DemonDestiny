#pragma once
#include "Enemy.h"
#include "Boulder.h"


class SpiderBoss : public Enemy
{
	int moveTimer;
	int shootTimer;
public:
	SpiderBoss();
	~SpiderBoss();
	void update(float);
	void shoot();
};

