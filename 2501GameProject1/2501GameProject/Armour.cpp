#include "Armour.h"


using namespace std;
Armour::Armour() : Item()
{
	name = "ARMOUR 1";
	value = 3000;
	defense = 100;
	type = "Armour";
}

Armour::Armour(string n, int v, int d, string t, int x, int y) :Item(n, v, t, x, y) {
	defense = d;
}

Armour::~Armour()
{
}

int Armour:: getDefense() { return defense; }
