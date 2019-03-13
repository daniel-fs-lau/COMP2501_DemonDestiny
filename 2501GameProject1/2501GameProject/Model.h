#pragma once
#include "Guy.h"
#include "Enemy.h"
#include "Spider.h"
#include "Tank.h"
#include "Ant.h"
#include "BigBoss.h"
#include "SpiderBoss.h"
#include "Area.h"
#include "Types.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
class Model {
	Types types;
	Guy g;
	int currentArea;
	std::vector<Creature*>creatures;
	std::vector<Updateable*> updateables;
	std::vector <vector<int>> rooms;
	Area*** areas;
	std::vector<Guy*> guys;
	sf::Vector2f player;
	int state;
	int levelCount;
	int sprite;
	int barrierN;
	int currentSubArea;
	sf::Vector2i mousePos;
	bool PAUSE;
public:

	//int **mapData;
	Model();
	~Model();
	//std::vector<Renderable*> getRenderables();
	std::vector<Updateable*> getUpdateables();
	std::vector<Guy*> getGuys();
	//std::vector<Enemy*> getEnemies();
	//std::vector<Creature*> getCreatures();

	Types getTypes();
	Guy getGuy();
	float getplayerX();
	float getplayerY();
	void setplayerX(float);
	void setplayerY(float);
	Area*** getAreas();
	std::vector <vector<int>> getRooms();
	int getmapRows();
	int getmapCols();
	int getcurrentArea();
	void setcurrentArea(int);
	void setmapRows(int);
	void setmapCols(int);
	int getlevelCount();
	int getSprite();
	void setSprite(int s);
	bool makeMap(string);
	std::vector<Creature*>& getCreatures();
	int getBarrierN();
	void setBarrierN(int);
	int getcurrentSubArea();
	void setcurrentSubArea(int);
	int getState();
	void setState(int);
	sf::Vector2i  getMousePos();
	void setMousePos(sf::Vector2i);
	void setPause(bool);
	bool getPause();
};