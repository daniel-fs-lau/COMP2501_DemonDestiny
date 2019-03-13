#include "CreatureStone.h"


using namespace std;


CreatureStone::CreatureStone() :Item()
{
	name = "egg";
	value = 50000;
	type = "Creature Egg";
}

CreatureStone::CreatureStone(string n, int v, string t, int x, int y) :Item(n, v, t, x, y) {

}

CreatureStone::~CreatureStone()
{
}
