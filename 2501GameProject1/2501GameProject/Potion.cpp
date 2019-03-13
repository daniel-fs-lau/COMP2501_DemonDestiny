#include "Potion.h"


using namespace std;


Potion::Potion():Item()
{
	name = "POTION 1";
	value = 500;
	heal = 100;
	type = "Potion";
}


Potion::~Potion()
{
}
