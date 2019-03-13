#include "Guy.h"

using namespace std;
Guy::Guy() :Updateable()
{
	health = 100;
	maxHealth = 100;
	speed = 5;
	pos.x = 1152;
	pos.y = 640;
	state = NORMAL;
	statusTimer = 3;
	numCols = 5;
	boxSize = 32;
	inventorySize = 15;
	selectedItem = 0;
	equippedCount = 3;
	bossKills = 0;
	inventoryTopCorner = new sf::Vector2f(640 - 1 - numCols*boxSize, 1);
	equipped.push_back(new Weapon("Tree Branch", 2, 1000, "Weapon", 0, 0));
	equipped.push_back(new Armour("Rags", 3, 5, "Armour", 0, 0));
	equipped.push_back(new CreatureStone("Little Egg", 10,"Creature Egg", 0, 0));
	id = "player";

	for (float i = 0; i < inventory.size(); i++) {
		//cout << inventory[i]->getName() << endl;
	}
}
Guy::~Guy() {

}

void Guy::update(float deltaTime) {
//	pos = (sf::Vector2f(pos.x + dir.x, pos.y + dir.y));
	if (status == POISON&&statusTimer>0) {
		statusTimer -= 0.01;
		health -= 0.01;
	}
	if (state == RIDING) {
		pos.x = target.x;
		pos.y = target.y;
	}
	else {
		size = 64;
		speed = 5;
	}
}

void Guy::useItem(Item* item) {
	if (item->getType() == "Weapon") {
		Item* temp = item;
		//Switch equipped weapon with used item
		inventory[selectedItem] = equipped[0];
		equipped[0] = item;
	}
	else if (item->getType() == "Armour") {
		Item* temp = item;
		//Switch equipped armour with used item
		inventory[selectedItem] = equipped[1];
		equipped[1] = item;
	}
	else if (item->getType() == "Creature Egg") {
		Item* temp = item;
		//Switch equipped egg with used item
		inventory[selectedItem] = equipped[2];
		equipped[2] = item;
	}
	else {

	}
}

void Guy::deleteItem(int index) {
	delete(inventory[index]);
	itemCount--;
	inventory.erase(inventory.begin() + index);
}

std::vector<Item*>&Guy::getInventory() { return inventory; }
std::vector<Item*>&Guy::getEquipped() { return equipped; }
int Guy::getEquippedCount() { return equippedCount; }
void Guy::setInventory(std::vector<Item*> newInventory) { inventory = newInventory; }
void Guy::addItem(Item* item) { inventory.push_back(item); itemCount++; }
float Guy::getStatusTimer() { return statusTimer; }
void Guy::setStatusTimer(float s) { statusTimer = s; }
int Guy::getCols() { return numCols; }
int Guy::getBoxSize() { return boxSize; }
int Guy::getInventorySize() { return inventorySize; }
sf::Vector2f Guy::getInventoryTopCorner(){ return *inventoryTopCorner; }
int Guy::getItemCount() { return itemCount; }
void Guy::setItemCount(int i) { itemCount = i; }
int Guy::getSelectedItem() { return selectedItem; }
void Guy::setSelectedItem(int s) { selectedItem = s; }
std::vector<Projectile*>& Guy::getProjectiles() { return projectiles; }
int Guy::getBossKills() { return bossKills; }
void Guy::setBossKills(int s) { bossKills = s; }
