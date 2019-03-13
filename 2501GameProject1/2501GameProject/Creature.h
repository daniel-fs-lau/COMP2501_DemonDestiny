#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Bullet.h"
#include "BigBullet.h"
class Creature : public Updateable {
protected:
	std::vector<Projectile*> projectiles;
	float angle;
	float charge;
	bool CHARGING;
public:
	float dx, dy, dist;
	Creature();
	~Creature();
	virtual void update(float)=0;
	virtual void follow()=0;
	virtual void ride() = 0;
	virtual void shoot() = 0;
	std::vector<Projectile*>& getProjectiles();
	virtual float getAngle()=0;
	virtual void setAngle(float)=0;
	virtual float getCharge() = 0;
	virtual void setCharge(float) = 0;
	virtual bool getCharging() = 0;
	virtual void setCharging(bool) = 0;
	float getDist();
	//void render(sf::RenderWindow*);
};