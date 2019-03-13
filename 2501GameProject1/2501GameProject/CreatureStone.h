#pragma once
#include "Item.h"
#include <string>


class CreatureStone : public Item {


public:
	CreatureStone();
	CreatureStone(string n, int v, string t, int x, int y);
	~CreatureStone();
};

