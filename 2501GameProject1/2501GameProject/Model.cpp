#include "Model.h"

Model::Model() {
	//renderables.push_back(&g);
	//updateables.push_back(&g);
	guys.push_back(&g);
	PAUSE = false;
	levelCount = 5;
	currentArea = 0;
	currentSubArea = 0;
	state = getTypes().TITLE;
	areas = new Area**[levelCount];
	for (int i = 0; i <levelCount; i++) {
		areas[i] = new Area*[5];
	}
	for (float i = 0; i < 1; i++) {
		Ant *s = new Ant;
		s->setPosY(3 * 64);
		s->setPosX(4 * 64);
		creatures.push_back(s);
	}
;
	barrierN = 3;
	//Data
	areas[0][0] = new Area("Assets/mapdata.txt");
	areas[1][0] = new Area("Assets/mapdata10.txt");
	areas[1][1] = new Area("Assets/mapdata11.txt");
	areas[1][2] = new Area("Assets/mapdata12.txt");
	areas[1][4] = new Area("Assets/mapdata14.txt");
	areas[2][0] = new Area("Assets/mapdata20.txt");
	areas[2][1] = new Area("Assets/mapdata21.txt");
	areas[2][2] = new Area("Assets/mapdata22.txt");
	areas[2][3] = new Area("Assets/mapdata23.txt");
	areas[3][0] = new Area("Assets/mapdata30.txt");
	areas[3][2] = new Area("Assets/mapdata32.txt");
	areas[3][3] = new Area("Assets/mapdata33.txt");
	areas[3][4] = new Area("Assets/mapdata34.txt");
	areas[4][0] = new Area("Assets/mapdata40.txt");
	areas[4][1] = new Area("Assets/mapdata41.txt");
	areas[4][3] = new Area("Assets/mapdata43.txt");
	areas[4][4] = new Area("Assets/mapdata44.txt");

	areas[3][0]->getEnemies().push_back(new BigBoss);
	areas[1][0]->getEnemies().push_back(new SpiderBoss);
}

Model::~Model() {

}

//std::vector<Renderable*> Model::getRenderables() { return renderables; }
std::vector<Updateable*> Model::getUpdateables() { return updateables; }
std::vector<Guy*> Model::getGuys() { return guys; }
Guy Model::getGuy() { return g; }
//std::vector<Enemy*> Model::getEnemies() { return enemies; }
//std::vector<Creature*>Model::getCreatures() { return creatures; }
float Model::getplayerX() { return player.x; }
float Model::getplayerY() { return player.y; }
void Model::setplayerX(float x) { player.x = x; }
int Model::getSprite() { return sprite; }
void Model::setSprite(int s) { sprite = s; }
void Model::setplayerY(float y) { player.y = y; }
Area*** Model::getAreas() { return areas; }
/*int Model::getmapCols() { return mapCols; }
int Model::getmapRows() { return mapRows; }
void Model::setmapCols(int c) { mapCols = c; }
void Model::setmapRows(int r) { mapRows = r; }*/
int Model::getcurrentArea() {return currentArea;}
void Model::setcurrentArea(int c) { currentArea = c; }
int Model::getlevelCount() { return levelCount; }
std::vector<Creature*>&Model::getCreatures() { return creatures; }
int Model::getBarrierN() { return barrierN; }
void Model::setBarrierN(int b) { barrierN = b; }
int Model::getcurrentSubArea() { return currentSubArea; }
void Model::setcurrentSubArea(int c) { currentSubArea = c; }
Types Model::getTypes() {return types;}
int Model::getState() { return state; }
void Model::setState(int s) {state = s;}
sf::Vector2i Model::getMousePos() { return mousePos; }
void Model::setMousePos(sf::Vector2i m) { mousePos = m; }
bool Model::getPause() { return PAUSE; }
void Model::setPause(bool c) { PAUSE = c; }