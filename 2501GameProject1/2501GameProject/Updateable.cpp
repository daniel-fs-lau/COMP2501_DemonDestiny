#include "Updateable.h"



Updateable::Updateable()
{
	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	health = 15;
	maxHealth = 15;
	speed = 3;
	state = 0;
	status = 0;
	size = 64;
}
Updateable::Updateable(float x, float y, float dx, float dy, int st, float sp) {
	pos.x = x;
	pos.y = y;
	dir.x = dx;
	dir.y = dy;
	state = st;
	speed = sp;
	health = 15;
	maxHealth = 15;
	size = 64;
}
void Updateable::print() {
	std::cout << "NAME: " << id << std::endl;
	std::cout << "Pos: (" << pos.x << "," << pos.y <<")"<< std::endl;
	std::cout << "Dir: (" << dir.x << "," << dir.y <<")"<< std::endl;
	std::cout << "Health: " << health << std::endl;
	std::cout << "MaxHealth: " << maxHealth << std::endl;
	std::cout << "State: " << state << std::endl;
	std::cout << "Speed: " << speed << std::endl;
	std::cout << "Status: " << status << std::endl << std::endl;
}
void Updateable::setPosX(float x) { pos.x = x; }
void Updateable::setPosY(float y) { pos.y = y; }
float Updateable::getPosX() { return pos.x; }
float Updateable::getPosY() { return pos.y; }
void Updateable::setDirX(float x) { dir.x = x; }
void Updateable::setDirY(float y) { dir.y = y; }
float Updateable::getDirX() { return dir.x; }
float Updateable::getDirY() { return dir.y; }
int Updateable::getState() { return state; }
void Updateable::setState(int s) { state = s; }
int Updateable::getStatus() { return status; }
void Updateable::setStatus(int s) { status = s; }
float Updateable::getSpeed() { return speed; }
void Updateable::setSpeed(float s) { speed = s; }
float Updateable::getHealth() { return health; }
void Updateable::setHealth(float h) { health = h; }
float Updateable::getMaxHealth() { return maxHealth; }
void Updateable::setMaxHealth(float h) { maxHealth = h; }
sf::Vector2f Updateable::getTarget() { return target; }
void Updateable::setTarget(sf::Vector2f t) { target = t; }
sf::Vector2f Updateable::getPos() { return pos; }
std::string Updateable::getID() { return id; }
int Updateable::getSize() { return size; }
void Updateable::setSize(int s) { size = s; }
/*void Updateable::setTarget(sf::Vector2f t) { target = t; }*/