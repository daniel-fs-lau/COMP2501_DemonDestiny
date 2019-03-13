#include "Item.h"

using namespace std;
Item::Item()
{
	name = "ITEM!!!!";
	type = "ITEM";
	value = 1000;
	itemX = -10000;
	itemY = -10000;
}

Item::Item(Item& other) {
	name = other.name;
	value = other.value;
	type = other.type;
	itemX = other.itemX;
	itemY = other.itemY;
	damage = other.damage;
	defense = other.defense;
}

Item::Item(string n, int v, string t, int x, int y) {
	name = n;
	value = v;
	type = t;
	itemX = x;
	itemY = y;
}


Item::~Item()
{
}

int Item::getValue() { return value; }
void Item::setValue(int v) { value = v; }
std::string Item::getName() {	return name;}
std::string Item::getType() {	return type;}
int Item::getPosX() {	return itemX;}
int Item::getPosY() {	return itemY;}
void Item::setPosX(int x) {	itemX = x;}
void Item::setPosY(int y) {	itemY = y;}
int Item::getDamage() { return -1; }
int Item::getDefense() { return -1; }