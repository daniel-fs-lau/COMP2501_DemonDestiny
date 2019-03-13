#pragma once
#include "Creature.h"
class Spider : public Creature{
	int shootTimer;
public:
	Spider();
	~Spider();
	void update(float);
    void shoot();
	void ride();
	void follow();
	float getAngle();
	void setAngle(float a);
	float getCharge() { return 0; };
	void setCharge(float) {};
	bool getCharging() { return false; };
	void setCharging(bool) {};
};

