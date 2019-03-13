#pragma once
#include "Item.h"
#include <string>


class Potion : public Item{

	int heal;

public:
	Potion();
	~Potion();
};

