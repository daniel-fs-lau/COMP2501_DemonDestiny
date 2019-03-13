#include "Area.h"



Area::Area()
{
	
}

Area::Area(std::string md) {
	std::ifstream fileHndl;
	fileHndl.open(md);
	fileHndl >> mapCols;
	fileHndl >> mapRows;
	mapData = new int *[mapRows];
	for (int i = 0; i < mapRows; i++) {
		mapData[i] = new int[mapCols];
	}

	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			fileHndl >> mapData[i][j];
		}
	}
	fileHndl.close();
	for (float i = 0; i < 3; i++) {
		Enemy *e = new Enemy;
		e->setPosX(i * 64);
		enemies.push_back(e);
		//	updateables.push_back(e);
		//cout << enemies[i]->getPosX() << endl;
	}
	/*for (float i = 0; i < 1; i++) {
		Spider *s = new Spider;
		s->setPosY(i *64);
		creatures.push_back(s);
	}*/
	Weapon *w1 = new Weapon("Emerald Wand",200, 30, "Weapon", 0, 0);
	w1->setPosX(64);
	w1->setPosY(64*4);
	items.push_back(w1);
	Weapon *w2 = new Weapon("Saphire Wand", 50, 12, "Weapon", 0, 0);
	w2->setPosX(128);
	w1->setPosY(64 * 5);
	items.push_back(w2);
	Weapon *w3 = new Weapon("Diamond Wand", 1000, 100, "Weapon", 0, 0);
	w3->setPosX(64*3);
	w1->setPosY(64 * 6);
	items.push_back(w3);
}

Area::~Area()
{
}

int Area::getConnectedRooms(int r) {
	return connectedRooms[r];
}
void Area::setConnectedRooms(int current, int desired) {
	connectedRooms[current] = desired;
}

int Area::getmapCols() { return mapCols; }
int Area::getmapRows() { return mapRows; }
void Area::setmapCols(int c) { mapCols = c; }
void Area::setmapRows(int r) { mapRows = r; }
std::vector<Enemy*>& Area::getEnemies() { return enemies; }
std::vector<Creature*>& Area::getCreatures() { return creatures; }
std::vector<Item*>& Area::getMapItem() { return items; }