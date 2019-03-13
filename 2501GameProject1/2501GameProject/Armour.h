#pragma once
#include "Item.h"
#include <string>

class Armour : public Item {

public:
	Armour();
	Armour(string n, int v, int a, string t, int x, int y);
	~Armour();
	int getDefense();
};

