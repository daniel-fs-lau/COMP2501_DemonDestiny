#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Updateable {

protected:
	sf::Vector2f target;
	sf::Vector2f pos;
	sf::Vector2f dir;
	int size;
	float health;
	float maxHealth;
	int state;
	std::string id;
	float speed;
	int status;
	static const int POISON = 1;
	static const int FOLLOWING = -1;
	static const int RIDING = -2;
	static const int NORMAL = -3;
public:
	Updateable() ;
	Updateable(float x, float y, float dx, float dy, int st, float sp);
	virtual void update(float)=0;
	void print();
	void setPosX(float);
	void setPosY(float);
	float getPosX();
	float getPosY();
	void setDirX(float);
	void setDirY(float);
	float getDirX();
	float getDirY();
	std::string getID();
	int getState();
	void setState(int);
	int getStatus();
	void setStatus(int);
	float getSpeed();
	void setSpeed(float);
	void setHealth(float);
	float getHealth();
	void setMaxHealth(float);
	float getMaxHealth();
	void setTarget(sf::Vector2f t);
	sf::Vector2f getTarget();
	sf::Vector2f getPos();
	int getSize();
	void setSize(int);
//	sf::Vector2f target;
//	void Updateable::setTarget(sf::Vector2f t);
};