#pragma once
#include "Creature.h"
class Ant : public Creature {
	int shootTimer;
public:
	Ant();
	~Ant();
	void update(float);
	void shoot();
	void ride();
	void follow();
	float getAngle() ;
	void setAngle(float a) ;
	float getCharge() { return 0; };
	void setCharge(float) {};
	bool getCharging() { return false; };
	void setCharging(bool) {};
};

