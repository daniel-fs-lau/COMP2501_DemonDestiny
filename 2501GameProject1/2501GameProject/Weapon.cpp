#include "Weapon.h"

using namespace std;


Weapon::Weapon() :Item()
{
	name = "WEAPON 1";
	value = 2000;
	damage = 5;
	type = "Weapon";
	itemX = -10000;
	itemY = -10000;
}

Weapon::Weapon(string n, int v, int d, string t, int x, int y) :Item(n, v, t, x, y ) {
	damage = d;
}

Weapon::~Weapon()
{
}

int Weapon::getDamage() { return damage; }