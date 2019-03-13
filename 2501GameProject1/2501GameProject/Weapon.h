#pragma once
#include "Item.h"
#include <string>


class Weapon : public Item{

public:
	Weapon();
	Weapon(string, int, int, string, int, int);
	~Weapon();
	int getDamage();
};

