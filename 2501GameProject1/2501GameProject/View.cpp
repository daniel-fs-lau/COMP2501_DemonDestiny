#include "View.h"

View::View() {

}

View::View(Model* w) {
	model = w;
	width = 1152;
	height = 640;
	window.create(sf::VideoMode(width, height), "COMP2501 Demo");
	window.setFramerateLimit(120);
	colour.a = 0;
	SHOWINVENTORY = false;
	viewWindow.setCenter(sf::Vector2f(width / 2, height / 2));
	viewWindow.setSize(sf::Vector2f(width, height));
	setFloor(0);
	//Text/fonts
	if (!font.loadFromFile("Assets/COURIER.ttf"))
	{
		cout << "Couldn't load font!\n\n\n\n\n\n";
	}
	else {
		font.loadFromFile("Assets/COURIER.ttf");
	}
	text.setFont(font);
	text.setString("Reset text's value");
	text.setCharacterSize(15);
	text.setColor(sf::Color::Red);
	titlePic.loadFromFile("Assets/titlescreen.png");

	//Replace white pixels with transparent pixels
	playerPic.loadFromFile("Assets/ActorSpritesheet.png");
	setPixels(192, 192, playerPic, colour);
	enemyPic.loadFromFile("Assets/enemy.gif");
	setPixels(64, 64, enemyPic, colour);
	creaturePic.loadFromFile("Assets/creature.gif");
	setPixels(64, 64, creaturePic, colour);
	bigBossPic.loadFromFile("Assets/bigboss.gif");
	setPixels(64, 64, bigBossPic, colour);
	weaponPic.loadFromFile("Assets/weapon.png");
	setPixels(32, 32, weaponPic, colour);
	projectilePic.loadFromFile("Assets/bullet.png");
	setPixels(16, 16, projectilePic, colour);
	tankPic.loadFromFile("Assets/bigBoss2.gif");
	setPixels(64, 64, tankPic, colour);
	armourPic.loadFromFile("Assets/armour.png");
	setPixels(32, 32, armourPic, colour);
	eggPic[0].loadFromFile("Assets/egg1.png");
	setPixels(32, 32, eggPic[0], colour);
	eggPic[1].loadFromFile("Assets/egg2.png");
	setPixels(32, 32, eggPic[1], colour);
	eggPic[2].loadFromFile("Assets/egg3.png");
	setPixels(32, 32, eggPic[2], colour);
	eggPic[3].loadFromFile("Assets/egg4.png");
	setPixels(32, 32, eggPic[3], colour);
	eggPic[4].loadFromFile("Assets/egg5.png");
	setPixels(32, 32, eggPic[4], colour);
	antPic.loadFromFile("Assets/ant.gif");
	setPixels(32, 32, antPic, colour); 
	spiderBossPic.loadFromFile("Assets/bigBoss3.gif");
	setPixels(64, 64, spiderBossPic, colour);

	makeSprite(titleSprite, titlePic, titleTexture);
	makeSprite(playerSprite, playerPic, playerTexture);
	makeSprite(enemySprite, enemyPic, enemyTexture);
	makeSprite(creatureSprite, creaturePic, creatureTexture);
	creatureSprite.setOrigin(32, 32);
	makeSprite(bigBossSprite, bigBossPic, bigBossTexture);
	makeSprite(weaponSprite, weaponPic, weaponTexture);
	makeSprite(projectileSprite, projectilePic, projectileTexture);
	makeSprite(tankSprite, tankPic, tankTexture);
	tankSprite.setOrigin(32, 32);
	makeSprite(armourSprite, armourPic, armourTexture);
	makeSprite(eggSprite[0], eggPic[0], eggTexture[0]);
	makeSprite(eggSprite[1], eggPic[1], eggTexture[1]);
	makeSprite(eggSprite[2], eggPic[2], eggTexture[2]);
	makeSprite(eggSprite[3], eggPic[3], eggTexture[3]);
	makeSprite(eggSprite[4], eggPic[4], eggTexture[4]);
	makeSprite(antSprite, antPic, antTexture);
	antSprite.setOrigin(16, 16);
	makeSprite(spiderBossSprite, spiderBossPic, spiderBossTexture);

	playerArray = new sf::VertexArray;
	playerStates = new sf::RenderStates;
	playerArray->setPrimitiveType(sf::Quads);
	playerArray->resize(4);

	crateTexture.loadFromImage(cratePic);
	crateTexture.setSmooth(true);
	mapArray = new sf::VertexArray;
	states = new sf::RenderStates;
	mapSprites = new sf::Sprite*[model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows()];
	for (int i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows(); i++) {
		mapSprites[i] = new sf::Sprite[model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols()];
	}
	
	createmapArray(mapArray, states);
}

View::~View() {

}

void View::rotateCreature(int type) {
	if (type == 0) {
		creatureSprite.setRotation((model->getCreatures()[0]->getAngle() * 180 / PI) + 180);
	}
	else if (type == 1) {
		tankSprite.setRotation((model->getCreatures()[0]->getAngle() * 180 / PI) + 180);
	}
	else if (type == 2) {
		antSprite.setRotation((model->getCreatures()[0]->getAngle() * 180 / PI) + 180);
	}
}

void View::createmapArray(sf::VertexArray* ma, sf::RenderStates* s) {
	ma->clear();
	ma->setPrimitiveType(sf::Quads);
	ma->resize(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows()*model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 4);
	for (int i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows(); i++)
	{
		for (int j = 0; j < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols(); j++)
		{
			//Generates map array quad tiles
			int tileCol = ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[i][j]) % 4) * 64;
			int tileRow = floor((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[i][j]) / 4) * 64;

			sf::Vertex* tileQuad = &(*ma)[(j + (i * model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols())) * 4];

			tileQuad[0].position = sf::Vector2f(j * 64, i * 64);
			tileQuad[1].position = sf::Vector2f((j + 1) * 64, i * 64);
			tileQuad[2].position = sf::Vector2f((j + 1) * 64, (i + 1) * 64);
			tileQuad[3].position = sf::Vector2f(j * 64, (i + 1) * 64);

			tileQuad[0].texCoords = sf::Vector2f(tileCol, tileRow);
			tileQuad[1].texCoords = sf::Vector2f(tileCol + 64, tileRow);
			tileQuad[2].texCoords = sf::Vector2f(tileCol + 64, tileRow + 64);
			tileQuad[3].texCoords = sf::Vector2f(tileCol, tileRow + 64);


			s->texture = &this->floorTexture;
		}
	}
	//}
}

void::View::displayInventory() {
	/*cout << "\t\t[INVENTORY]" << endl;
	for (unsigned i = 0; i < model->getGuys()[0]->getInventory().size(); i++) {//Displaying the inventory
		cout <<"Item Slot "<< i+1 << ")" << endl;
		cout <<"\tName: "<< model->getGuys()[0]->getInventory()[i]->getName()<<endl;
		if (model->getGuys()[0]->getInventory()[i]->getType() == "Weapon") {
			cout <<"\tDamage: "<< model->getGuys()[0]->getInventory()[i]->getDamage();
		}
		cout << endl;
	}
	cout << endl;*/
	// cycle through the inventory
	int row = 0, col = 0;
	//Rectangle for the background
	sf::RectangleShape bg(sf::Vector2f(model->getGuys()[0]->getBoxSize()*model->getGuys()[0]->getCols()+ (2*(model->getGuys()[0]->getBoxSize())),
									  (model->getGuys()[0]->getBoxSize()*(model->getGuys()[0]->getInventorySize()))/model->getGuys()[0]->getCols()+ (2*(model->getGuys()[0]->getBoxSize()))+80));
	bg.setPosition(sf::Vector2f(((36 * 64 - (36 * 64 - model->getGuys()[0]->getPosX()) + ((viewWindow.getSize().x / 2) - (model->getGuys()[0]->getBoxSize() * model->getGuys()[0]->getCols())) + col*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()) + col * 6)-model->getGuys()[0]->getBoxSize()-16,
		((20 * 64 - (20 * 64 - model->getGuys()[0]->getPosY()) - ((viewWindow.getSize().y / 2) - (model->getGuys()[0]->getBoxSize()*(round(model->getGuys()[0]->getInventorySize()) / model->getGuys()[0]->getCols()))) + row*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize() * 2) + row * 6)-16));
	bg.setFillColor(sf::Color(200, 200, 200));
	bg.setOutlineColor(sf::Color(100,120,160));
	bg.setOutlineThickness(3);
	window.draw(bg);
	//Rectangles for the item slots
	for (int i = 0; i < model->getGuys()[0]->getInventorySize(); i++) {
		col = i % model->getGuys()[0]->getCols();
		row = i / model->getGuys()[0]->getCols();
		sf::RectangleShape slot(sf::Vector2f(model->getGuys()[0]->getBoxSize(), model->getGuys()[0]->getBoxSize()));
		slot.setPosition(sf::Vector2f(((36 * 64 - (36 * 64 - model->getGuys()[0]->getPosX()) + ((viewWindow.getSize().x / 2) - (model->getGuys()[0]->getBoxSize() * model->getGuys()[0]->getCols())) + col*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()) + col * 6) - model->getGuys()[0]->getBoxSize()+6,
									  (20 * 64 - (20 * 64 - model->getGuys()[0]->getPosY()) - ((viewWindow.getSize().y /2)- (model->getGuys()[0]->getBoxSize()*(round(model->getGuys()[0]->getInventorySize())/model->getGuys()[0]->getCols()))) + row*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()*2)+row*6));
		slot.setOutlineColor(sf::Color(200,200,0));
		if (model->getGuys()[0]->getSelectedItem() == i) {
			slot.setOutlineColor(sf::Color(0, 200, 200));
		}
		slot.setOutlineThickness(3);
		slot.setFillColor(sf::Color::White);
		window.draw(slot);
	}
	//Rectangles for the equipment slots
	for (int i = 0; i < model->getGuys()[0]->getEquippedCount(); i++) {
		col = i % model->getGuys()[0]->getCols();
		row = i / model->getGuys()[0]->getCols();
		sf::RectangleShape slot(sf::Vector2f(model->getGuys()[0]->getBoxSize(), model->getGuys()[0]->getBoxSize()));
		slot.setPosition(sf::Vector2f(((36 * 64 - (36 * 64 - model->getGuys()[0]->getPosX()) + ((viewWindow.getSize().x / 2) - (model->getGuys()[0]->getBoxSize() * model->getGuys()[0]->getCols())) + col*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()) + col * 6) - model->getGuys()[0]->getBoxSize() + 6,
			(20 * 64 - (20 * 64 - model->getGuys()[0]->getPosY()) - ((viewWindow.getSize().y / 2) - (model->getGuys()[0]->getBoxSize()*(round(model->getGuys()[0]->getInventorySize()) / model->getGuys()[0]->getCols()))) + row*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize() * 5/2) + row * 6+(4* model->getGuys()[0]->getBoxSize())));
		slot.setOutlineColor(sf::Color(200, 200, 0));
		slot.setOutlineThickness(3);
		if (i == 0) {
			slot.setFillColor(sf::Color::Red);
		}
		else if(i==1) {
			slot.setFillColor(sf::Color::Blue);
		}
		else if (i == 2) {
			slot.setFillColor(sf::Color::Green);
		}
		window.draw(slot);
	}
	//Drawing the items and drawing text
	for (int i = 0; i < model->getGuys()[0]->getItemCount(); i++) {
			col = i % model->getGuys()[0]->getCols();
			row = i / model->getGuys()[0]->getCols();
			model->getGuys()[0]->getInventory()[i]->setPosX(((36 * 64 - (36 * 64 - model->getGuys()[0]->getPosX()) + ((viewWindow.getSize().x / 2) - (model->getGuys()[0]->getBoxSize() * model->getGuys()[0]->getCols())) + col*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()) + col * 6) - model->getGuys()[0]->getBoxSize() + 6);
			model->getGuys()[0]->getInventory()[i]->setPosY((20 * 64 - (20 * 64 - model->getGuys()[0]->getPosY()) - ((viewWindow.getSize().y / 2) - (model->getGuys()[0]->getBoxSize()*(round(model->getGuys()[0]->getInventorySize()) / model->getGuys()[0]->getCols()))) + row*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize() * 2) + row * 6);
			if (model->getGuys()[0]->getInventory()[i]->getType() == "Weapon") {
				weaponSprite.setPosition(sf::Vector2f(model->getGuys()[0]->getInventory()[i]->getPosX(), model->getGuys()[0]->getInventory()[i]->getPosY()));
				window.draw(weaponSprite);
			}else if (model->getGuys()[0]->getInventory()[i]->getType() == "Armour") {
				armourSprite.setPosition(sf::Vector2f(model->getGuys()[0]->getInventory()[i]->getPosX(), model->getGuys()[0]->getInventory()[i]->getPosY()));
				window.draw(armourSprite);
			}else if (model->getGuys()[0]->getInventory()[i]->getType() == "Creature Egg") {
				int spriteN = 0;
				if (model->getGuys()[0]->getInventory()[i]->getName() == "Spider Egg") {
					spriteN = 0;
				}else if (model->getGuys()[0]->getInventory()[i]->getName() == "Tank Egg") {
					spriteN = 1;
				}
				else if (model->getGuys()[0]->getInventory()[i]->getName() == "Little Egg") {
					spriteN = 4;
				}
				eggSprite[spriteN].setPosition(sf::Vector2f(model->getGuys()[0]->getInventory()[i]->getPosX(), model->getGuys()[0]->getInventory()[i]->getPosY()));
				window.draw(eggSprite[spriteN]);
			}
			if (model->getGuys()[0]->getSelectedItem() == i) {
				if (model->getGuys()[0]->getInventory()[i]->getType() == "Weapon") {
					text.setString("Type: " + model->getGuys()[0]->getInventory()[i]->getType() + "\nName: " + model->getGuys()[0]->getInventory()[i]->getName() + "\nDamage: " + to_string((int)model->getGuys()[0]->getInventory()[i]->getDamage()));
				}
				else if (model->getGuys()[0]->getInventory()[i]->getType() == "Armour") {
					text.setString("Type: " + model->getGuys()[0]->getInventory()[i]->getType() + "\nName: " + model->getGuys()[0]->getInventory()[i]->getName() + "\nDefense: " + to_string((int)model->getGuys()[0]->getInventory()[i]->getDefense()));
				}else if (model->getGuys()[0]->getInventory()[i]->getType() == "Creature Egg") {
					text.setString("Type: " + model->getGuys()[0]->getInventory()[i]->getType() + "\nName: " + model->getGuys()[0]->getInventory()[i]->getName());
				}
				text.setPosition(sf::Vector2f(bg.getPosition().x + 20, bg.getPosition().y + 5 + model->getGuys()[0]->getBoxSize()*5));
				window.draw(text);
			}
	}
	//Drawing equipment items
	for (int i = 0; i < model->getGuys()[0]->getEquippedCount(); i++) {
			col = i % model->getGuys()[0]->getCols();
			row = i / model->getGuys()[0]->getCols();
			model->getGuys()[0]->getEquipped()[i]->setPosX(((36 * 64 - (36 * 64 - model->getGuys()[0]->getPosX()) + ((viewWindow.getSize().x / 2) - (model->getGuys()[0]->getBoxSize() * model->getGuys()[0]->getCols())) + col*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize()) + col * 6) - model->getGuys()[0]->getBoxSize() + 6);
			model->getGuys()[0]->getEquipped()[i]->setPosY((20 * 64 - (20 * 64 - model->getGuys()[0]->getPosY()) - ((viewWindow.getSize().y / 2) - (model->getGuys()[0]->getBoxSize()*(round(model->getGuys()[0]->getInventorySize()) / model->getGuys()[0]->getCols()))) + row*model->getGuys()[0]->getBoxSize() - model->getGuys()[0]->getBoxSize() * 5 / 2) + row * 6 + (4 * model->getGuys()[0]->getBoxSize()));
			if (model->getGuys()[0]->getEquipped()[i]->getType() == "Weapon") {
				weaponSprite.setPosition(sf::Vector2f(model->getGuys()[0]->getEquipped()[i]->getPosX(), model->getGuys()[0]->getEquipped()[i]->getPosY()));
				window.draw(weaponSprite);
			}
			else if (model->getGuys()[0]->getEquipped()[i]->getType() == "Armour") {
				armourSprite.setPosition(sf::Vector2f(model->getGuys()[0]->getEquipped()[i]->getPosX(), model->getGuys()[0]->getEquipped()[i]->getPosY()));
				window.draw(armourSprite);
			}
			else if (model->getGuys()[0]->getEquipped()[i]->getType() == "Creature Egg") {
				int spriteN = 0;
				if (model->getGuys()[0]->getEquipped()[i]->getName() == "Spider Egg") {
					spriteN = 0;
				}
				else if (model->getGuys()[0]->getEquipped()[i]->getName() == "Tank Egg") {
					spriteN = 1;
				}
				else if (model->getGuys()[0]->getEquipped()[i]->getName() == "Little Egg") {
					spriteN = 4;
				}
				eggSprite[spriteN].setPosition(sf::Vector2f(model->getGuys()[0]->getEquipped()[i]->getPosX(), model->getGuys()[0]->getEquipped()[i]->getPosY()));
				window.draw(eggSprite[spriteN]);
			}
	}
}

// Change the image for the player based on the sprite number
void View::updatePlayerSprite(sf::VertexArray* pa, sf::RenderStates* s) {

	int tileCol = ((model->getSprite() % 3) * 64);
	int tileRow = floor((model->getSprite()) / 3) * 64;

	sf::Vertex* tileQuad = &(*pa)[0];

	tileQuad[0].position = sf::Vector2f(model->getGuy().getPosX(), model->getGuy().getPosY());
	tileQuad[1].position = sf::Vector2f((model->getGuy().getPosX() + 64), model->getGuy().getPosY());
	tileQuad[2].position = sf::Vector2f((model->getGuy().getPosX() + 64), (model->getGuy().getPosY() + 64));
	tileQuad[3].position = sf::Vector2f(model->getGuy().getPosX(), (model->getGuy().getPosY() + 64));

	tileQuad[0].texCoords = sf::Vector2f(tileCol, tileRow);
	tileQuad[1].texCoords = sf::Vector2f(tileCol + 64, tileRow);
	tileQuad[2].texCoords = sf::Vector2f(tileCol + 64, tileRow + 64);
	tileQuad[3].texCoords = sf::Vector2f(tileCol, tileRow + 64);


	s->texture = &this->playerTexture;
}

void View::makeHealthBar(float sX, float sY, float pX, float pY, float cHP, float mHP, sf::Color outlineColor) {
	sf::RectangleShape out(sf::Vector2f(sX, sY));
	out.setPosition(sf::Vector2f(pX, pY - 10));
	out.setOutlineColor(outlineColor);
	out.setOutlineThickness(2);
	out.setFillColor(sf::Color::Black);

	sf::RectangleShape in(sf::Vector2f((sX - 4)*(cHP / mHP), sY - 4));
	in.setPosition(sf::Vector2f(pX + 2, pY - 8));
	in.setFillColor(sf::Color(255 * (1 - (cHP / mHP)), 255 * (cHP / mHP), 0));
	window.draw(out);
	window.draw(in);
}

void View::setFloor(int f) {
	if (f == 0) {
		floorPic.loadFromFile("Assets/spritesheetHub.png");
		model->setBarrierN(11);
	}
	if (f == 1) {
		floorPic.loadFromFile("Assets/spritesheetGraveyard.png");
		model->setBarrierN(3);
	}
	if (f == 2) {
		floorPic.loadFromFile("Assets/spritesheetWarehouse.png");
		model->setBarrierN(3);
	}
	if (f == 3) {
		floorPic.loadFromFile("Assets/spritesheetForest.png");
		model->setBarrierN(3);
	}
	if (f == 4) {
		floorPic.loadFromFile("Assets/spritesheetHouse.png");
		model->setBarrierN(3);
	}

	if (f != 0) {
		for (int i = 0; i < 256; i++) {
			for (int j = 0; j < 256; j++) {
				if (floorPic.getPixel(i, j) == colour) {
					floorPic.setPixel(i, j, floorPic.getPixel((i % 64 + 64), (j % 64 + 128)));
				}
			}
		}
	}
	if (f == 0) {
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 192; j++) {
				if (floorPic.getPixel(i, j) == colour) {
					floorPic.setPixel(i, j, floorPic.getPixel((i % 64), (j % 64 + 192)));
				}
			}
		}
		for (int i = 64; i < 128; i++) {
			for (int j = 0; j < 192; j++) {
				if (floorPic.getPixel(i, j) == colour) {
					floorPic.setPixel(i, j, floorPic.getPixel((i % 64 + 64), (j % 64 + 192)));
				}
			}
		}
		for (int i = 128; i < 192; i++) {
			for (int j = 0; j < 192; j++) {
				if (floorPic.getPixel(i, j) == colour) {
					floorPic.setPixel(i, j, floorPic.getPixel((i % 64 + 128), (j % 64 + 192)));
				}
			}
		}
		for (int i = 192; i < 256; i++) {
			for (int j = 0; j < 192; j++) {
				if (floorPic.getPixel(i, j) == colour) {
					floorPic.setPixel(i, j, floorPic.getPixel((i % 64 + 192), (j % 64 + 192)));
				}
			}
		}
	}

	floorTexture.loadFromImage(floorPic);
	floorTexture.setSmooth(true);
}

void View::render() {
	if (model->getState() == model->getTypes().TITLE) {
		titleSprite.setPosition(0, 0);
		window.draw(titleSprite);
		window.display();
	}
	else {
		window.clear();
		if (model->getGuys()[0]->getState() == -2) {
			viewWindow.setCenter(model->getCreatures()[0]->getPosX(), model->getCreatures()[0]->getPosY());
		}
		else {
			viewWindow.setCenter(model->getGuys()[0]->getPosX(), model->getGuys()[0]->getPosY());
		}
		window.setView(viewWindow);
		window.draw(*mapArray, *states);

		for (int i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size(); i++) {
			if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "enemy") {
				enemySprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY());
				window.draw(enemySprite);
			}
			else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "bigboss") {
				bigBossSprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY());
				window.draw(bigBossSprite);
			}
			else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "spiderboss") {
				spiderBossSprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY());
				window.draw(spiderBossSprite);
			}
			makeHealthBar(50, 10, model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX(),
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY(), model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getHealth(),
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getMaxHealth(), sf::Color::Red);
			for (unsigned j = 0; j < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles().size(); j++) {
				projectileSprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY());
				window.draw(projectileSprite);
			}
		}
		for (int i = 0; i < model->getCreatures().size(); i++) {
			//rotating creatureSprite. "DirX attribute is plceholder for an angleRotator"
			model->getCreatures()[i]->setDirX(atan2(model->getGuys()[0]->getPosY() - model->getCreatures()[i]->getPosY(), model->getGuys()[0]->getPosX() - model->getCreatures()[i]->getPosX()) * 57.296f);
			if (model->getCreatures()[i]->getID() == "spider") {
				creatureSprite.setPosition(model->getCreatures()[i]->getPosX() + 32, model->getCreatures()[i]->getPosY() + 32);//MODEL's creatures
				if (model->getCreatures()[i]->getDist() > 3 && model->getCreatures()[i]->getState() != -2) {
					creatureSprite.setRotation(model->getCreatures()[i]->getDirX() + 270);
					model->getCreatures()[i]->setAngle((model->getCreatures()[i]->getDirX() + 90)*PI / 180);
				}
				window.draw(creatureSprite);
			}else if (model->getCreatures()[i]->getID() == "tank") {
				tankSprite.setPosition(model->getCreatures()[i]->getPosX() + 32, model->getCreatures()[i]->getPosY() + 32);//MODEL's creatures
				if (model->getCreatures()[i]->getDist() > 3 && model->getCreatures()[i]->getState() != -2) {
					tankSprite.setRotation(model->getCreatures()[i]->getDirX() + 270);
					model->getCreatures()[i]->setAngle((model->getCreatures()[i]->getDirX() + 90)*PI / 180);
				}
				window.draw(tankSprite);
			}else if (model->getCreatures()[i]->getID() == "ant") {
				antSprite.setPosition(model->getCreatures()[i]->getPosX() + 32, model->getCreatures()[i]->getPosY() + 32);//MODEL's creatures
				if (model->getCreatures()[i]->getDist() > 3 && model->getCreatures()[i]->getState() != -2) {
					antSprite.setRotation(model->getCreatures()[i]->getDirX() + 270);
					model->getCreatures()[i]->setAngle((model->getCreatures()[i]->getDirX() + 90)*PI / 180);
				}
				window.draw(antSprite);
			}
			
			for (unsigned j = 0; j < model->getCreatures()[i]->getProjectiles().size(); j++) {
				projectileSprite.setPosition(model->getCreatures()[i]->getProjectiles()[j]->getPosX(),
					model->getCreatures()[i]->getProjectiles()[j]->getPosY());
				window.draw(projectileSprite);
			}
		}
		for (unsigned int i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem().size(); i++) {
			if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Weapon") {
				weaponSprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
				window.draw(weaponSprite);
			}else if(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Armour") {
				armourSprite.setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
				window.draw(armourSprite);
			}else if(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Creature Egg") {
				int spriteN=0;
				if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName() == "Spider Egg") {
					spriteN = 0;
				}
				else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName() == "Tank Egg") {
					spriteN = 1;
				}
				else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName() == "Little Egg") {
					spriteN = 4;
				}
				eggSprite[spriteN].setPosition(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
				window.draw(eggSprite[spriteN]);
			}
		}
		makeHealthBar(50, 10, model->getGuys()[0]->getPosX(), model->getGuys()[0]->getPosY(),
			model->getGuys()[0]->getHealth(), model->getGuys()[0]->getMaxHealth(), sf::Color::Blue);
		updatePlayerSprite(playerArray, playerStates);
		if (model->getGuys()[0]->getState() != -2) {
			window.draw(*playerArray, *playerStates);
		}
		for (unsigned j = 0; j < model->getGuys()[0]->getProjectiles().size(); j++) {
			projectileSprite.setPosition(model->getGuys()[0]->getProjectiles()[j]->getPosX(),
				model->getGuys()[0]->getProjectiles()[j]->getPosY());
			window.draw(projectileSprite);
		}
		if (SHOWINVENTORY)
			displayInventory();
		window.display();
	}
}
void View::death() {
	text.setString("You Have Died");
	text.setCharacterSize(50);
	text.setPosition(model->getGuys()[0]->getPos());
	window.draw(text);
	window.display();
	system("PAUSE");
}

void View::win() {
	text.setString("You Have Defeated Both Bosses!\n You win!");
	text.setCharacterSize(20);
	text.setPosition(model->getGuys()[0]->getPos());
	window.draw(text);
	window.display();
	system("PAUSE");
}


void View::setPixels(int x, int y, sf::Image& thePic, sf::Color colour) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (thePic.getPixel(i, j) == sf::Color::White) {
				thePic.setPixel(i, j, colour);
			}
		}
	}
}
void View::makeSprite(sf::Sprite& theSprite, sf::Image& thePic, sf::Texture& theTexture) {
	theTexture.loadFromImage(thePic);
	theSprite.setTexture(theTexture);
	theTexture.setSmooth(true);
}

sf::RenderWindow& View::getWindow() { return window; }
sf::VertexArray* View::getmapArray() { return mapArray; }
sf::RenderStates* View::getStates() { return states; }
bool View::getShowInventory() { return SHOWINVENTORY; }
void View::setShowInventory(bool s) {SHOWINVENTORY = s;}

