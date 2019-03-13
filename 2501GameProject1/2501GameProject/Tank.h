#pragma once

#include "Creature.h"
class Tank : public Creature {
	int shootTimer;
public:
	Tank();
	~Tank();
	void update(float);
	void shoot();
	void ride();
	void follow();
	float getAngle();
	void setAngle(float);
	float getCharge();
	void setCharge(float);
	bool getCharging();
	void setCharging(bool);
};

