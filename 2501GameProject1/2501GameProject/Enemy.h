#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Projectile.h"
#include "Weapon.h"
#include "Armour.h"
#include "CreatureStone.h"
class Enemy : public Updateable {
protected:
	std::vector<Projectile*> projectiles;
	std::vector<Item*>items;
public:
	Enemy();
	~Enemy();
	void update(float);
	void shoot();
	std::vector<Projectile*>& getProjectiles();
	std::vector<Item*>& getItems();
	//void render(sf::RenderWindow*);
};