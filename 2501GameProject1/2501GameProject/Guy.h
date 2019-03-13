#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Renderable.h"
#include <iostream>

#include "Item.h"
#include "Weapon.h"
#include "Armour.h"
#include "CreatureStone.h"
#include "Bullet.h"

class Guy : public Updateable{
	std::vector<Projectile*> projectiles;
	//Inventory Related
	std::vector<Item*> inventory;
	int bossKills;
	int itemCount;
	int numCols;
	int boxSize;
	int inventorySize;
	int selectedItem;
	std::vector<Item*> equipped;
	int equippedCount;
	sf::Vector2f* inventoryTopCorner;
	float statusTimer;
public:
	int test;
	Guy();
	~Guy();
	void update(float);
	std::vector<Item*>&getInventory();
	std::vector<Item*>&getEquipped();
	void Guy::setInventory(std::vector<Item*>);
	void Guy::addItem(Item*);
	int getCols();
	int getBoxSize();
	int getInventorySize();
	int getEquippedCount();
	sf::Vector2f getInventoryTopCorner();
	void setStatusTimer(float);
	float getStatusTimer();
	int getItemCount();
	void setItemCount(int);
	int getSelectedItem();
	void setSelectedItem(int);
	void useItem(Item*);
	void deleteItem(int);
	void setBossKills(int);
	int getBossKills();
	std::vector<Projectile*>& getProjectiles();

	//void render(sf::RenderWindow*);
};