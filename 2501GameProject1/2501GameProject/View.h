#pragma once
#include "Model.h"
#define PI 3.14159

class View {
	Model* model;
	sf::RenderWindow window;//V
	std::vector<std::vector<sf::Sprite> > gameWorld;
	sf::View viewWindow;
	

	//sf::Sprite ***mapSprites;
	sf::Sprite **mapSprites;
	sf::Sprite playerSprite;
	sf::Sprite enemySprite;
	sf::Sprite creatureSprite;
	sf::Sprite weaponSprite;
	sf::Sprite projectileSprite;
	sf::Sprite bigBossSprite;
	sf::Sprite titleSprite;
	sf::Sprite tankSprite;
	sf::Sprite armourSprite;
	sf::Sprite eggSprite[5];
	sf::Sprite antSprite;
	sf::Sprite spiderBossSprite;

	sf::Image playerPic;
	sf::Image cratePic;
	sf::Image floorPic;
	sf::Image enemyPic;
	sf::Image creaturePic;
	sf::Image weaponPic;
	sf::Image projectilePic;
	sf::Image bigBossPic;
	sf::Image titlePic;
	sf::Image tankPic;
	sf::Image armourPic;
	sf::Image eggPic[5];
	sf::Image antPic;
	sf::Image spiderBossPic;

	sf::Texture enemyTexture;
	sf::Texture playerTexture;
	sf::Texture crateTexture;
	sf::Texture floorTexture;
	sf::Texture creatureTexture;
	sf::Texture weaponTexture;
	sf::Texture projectileTexture;
	sf::Texture bigBossTexture;
	sf::Texture titleTexture;
	sf::Texture tankTexture;
	sf::Texture armourTexture;
	sf::Texture eggTexture[5];
	sf::Texture antTexture;
	sf::Texture spiderBossTexture;

	sf::VertexArray* mapArray;
	sf::RenderStates* states;
	sf::Color colour;

	sf::VertexArray* playerArray;
	sf::RenderStates* playerStates;
	
	sf::Font font;
	sf::Text text;

	bool SHOWINVENTORY;
public:
	View();
	View(Model* m);
	~View();
	int width, height;
	sf::RenderWindow& getWindow();
	void render();
	void createmapArray(sf::VertexArray*, sf::RenderStates*);
	void updatePlayerSprite(sf::VertexArray*, sf::RenderStates*);
	sf::VertexArray* getmapArray();
	sf::RenderStates* getStates();
	bool getShowInventory();
	void setShowInventory(bool);
	void makeHealthBar(float sizeX, float sizeY, float posX, float posY, float currHealth, float maxHealth,sf::Color);
	void displayInventory();
	void setFloor(int);
	void rotateCreature(int);
	void death();
	void win();
	void setPixels(int x, int y, sf::Image& pic, sf::Color colour);
	void makeSprite(sf::Sprite&, sf::Image&, sf::Texture&);
};