#pragma once
#include "Level.h"
#include "Enemy.h"
#include "Creature.h"
#include "Spider.h"
#include "Weapon.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Area : public Level{
	int mapRows, mapCols;
	std::vector<Enemy*>enemies;
	std::vector<Creature*>creatures;
	std::vector<Item*>items;
	int connectedRooms[5];
public:
	int **mapData;
	Area();
	Area(std::string);
	~Area();
	std::vector<Enemy*>& getEnemies();
	std::vector<Creature*>& getCreatures();
	std::vector<Item*>& getMapItem();
	int getmapRows();
	int getmapCols();
	void setmapRows(int);
	void setmapCols(int);
	int getConnectedRooms(int);
	void setConnectedRooms(int, int);
};

