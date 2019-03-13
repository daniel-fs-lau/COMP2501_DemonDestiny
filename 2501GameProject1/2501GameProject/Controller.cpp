#include "Controller.h"

Controller::Controller()
{
}

Controller::Controller(Model* m, View*v)
{
	model = m;
	view = v;
	frames = 0;
	target = 15;
	direction = 2;
	timer = 0;
	spaceTimer = 0;
	timers[0];
	timers[1] = 0;
	timers[2] = 0;
	timers[3] = 0;
	gc = new GuyController(m,v);
	sc = new SpiderController(m,v);
	tc = new TankController(m, v);
	ac = new AntController(m, v);
}

Controller::~Controller() {

}
void Controller::update(float deltaTime) {
	if (timer < 30) {
		timer++;
	}
	spaceTimer++;
	model->setMousePos(sf::Mouse::getPosition(view->getWindow()));
	gc->switchArea();

	model->getGuys()[0]->update(0);
	for (unsigned j = 0; j < model->getGuys()[0]->getProjectiles().size(); j++) {//looping over guys's projectile vector
																				 //has a target been set yet? is the enemy vector empty?
		if (model->getGuys()[0]->getProjectiles()[j]->getState() == -1) {
			//set target
			model->getGuys()[0]->getProjectiles()[j]->setTarget(sf::Vector2f((model->getMousePos().x + model->getGuys()[0]->getPosX() - view->width/2), (model->getMousePos().y + model->getGuys()[0]->getPosY() - view->height/2)));
			model->getGuys()[0]->getProjectiles()[j]->setState(0);

		}
		model->getGuys()[0]->getProjectiles()[j]->update(0);
		//cout << model->getGuys()[i]->getProjectiles().size() << endl;
		bool HIT = false;
		//Enemy is hit by guy
		for (unsigned k = 0; k < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size(); k++) {
			if (collision(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getPosX(),//did the bullet hit an enemy?
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getPosY(),
				model->getGuys()[0]->getProjectiles()[j]->getPosX(),
				model->getGuys()[0]->getProjectiles()[j]->getPosY(),
				64, 16)) {
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->setHealth(
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getHealth() - model->getGuys()[0]->getEquipped()[0]->getDamage());//enemy loses health
				HIT = true;
				break;
			}
		}
		if (HIT ||
			model->getGuys()[0]->getProjectiles()[j]->getPosX() > 36 * 64 ||//did it pass the boundries?
			model->getGuys()[0]->getProjectiles()[j]->getPosX() < 0 ||
			model->getGuys()[0]->getProjectiles()[j]->getPosY() > 20 * 64 ||//THIS NEEDS TO BE CHANGED TO BE BASED ON currentAREA'S MAPROW/COL
			model->getGuys()[0]->getProjectiles()[j]->getPosY() < 0) {
			delete(model->getGuys()[0]->getProjectiles()[j]);
			model->getGuys()[0]->getProjectiles().erase(model->getGuys()[0]->getProjectiles().begin() + j);
		}
	}
	model->getGuys()[0]->setTarget(model->getCreatures()[0]->getPos());
	if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getGuys()[0]->getPosY()) / 64)]//checks players position
		[(int)round((model->getGuys()[0]->getPosX()) / 64)] == 3)) {//is the payer's position on tile 10(poison)?
		model->getGuys()[0]->setStatus(1);//set to poison
		model->getGuys()[0]->setStatusTimer(3);
	}
	//CREATURE LOOP
	model->getCreatures()[0]->setTarget(model->getGuys()[0]->getPos());
	model->getCreatures()[0]->update(0);
	//If there are enemies and the enemy is close enough, shoot
	if (model->getCreatures()[0]->getID() == "spider") {
		if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size() > 0 &&
			collision(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[0]->getPosX(),
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[0]->getPosY(),
				model->getCreatures()[0]->getPosX(),
				model->getCreatures()[0]->getPosY(),
				300, 300)&&
			model->getCreatures()[0]->getState()!=-2) {
			model->getCreatures()[0]->shoot();
		}
	}
	else if (model->getCreatures()[0]->getID() == "tank") {

	}
	else {

	}

	for (unsigned i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size(); i++) {
		model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->setTarget(sf::Vector2f(model->getGuys()[0]->getPosX(), model->getGuys()[0]->getPosY()));
		model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->update(0);
		if (collision(model->getGuy().getPosX(),//If the player collides with the enemy
			model->getGuy().getPosY(),
			model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX(),
			model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY(),
			model->getGuys()[0]->getSize() , 64)) {
			if (timer >= 30) {
				//Armour calculator
				int damageToPlayer = 10 - model->getGuys()[0]->getEquipped()[1]->getDefense();
				if (damageToPlayer < 0) {
					damageToPlayer = 1;
				}
				model->getGuys()[0]->setHealth(model->getGuys()[0]->getHealth() - damageToPlayer);
				timer = 0;
			}
		}
		if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getHealth()<=0) {//If the enemy has no health
			//Drop an item from its items array
			if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "bigboss" ||
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "spiderboss") {
				model->getGuys()[0]->setBossKills(model->getGuys()[0]->getBossKills() + 1);
			}
			//if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getID() == "enemy") {//If its a normal enemy, drop a random item
				Item* itemPtr = model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getItems()[
					rand() % (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getItems().size())];
				itemPtr->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosX());
				itemPtr->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getPosY());
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem().push_back(itemPtr);
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().erase(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().begin() + i);
				continue;
			//}
		}
		//Looping over enemy projectiles
		if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size() <= 0) {
			break;
		}
		bool HIT = false;
		for (unsigned j = 0; j < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles().size(); j++) {//looping over each enemies's projectile vector
				 //Checking to see if target has been set
			//cout << model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getState() << endl;
			if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getState()==-1) {
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->setTarget
					(sf::Vector2f(model->getGuys()[0]->getPosX()+ model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getTarget().x, 
						model->getGuys()[0]->getPosY()+ model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getTarget().y));
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->setState(0);
			}
			model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->update(0);
			if (collision(model->getGuys()[0]->getPosX(),//did the bullet hit the player?
				model->getGuys()[0]->getPosY(),
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX(),
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY(),
				64, 16)) {
				model->getGuys()[0]->setHealth(model->getGuys()[0]->getHealth() - 5);
				HIT = true;
			}
			if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getID() == "boulder") {
				if (collision(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getTarget().x,//did the boulder reach the target
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getTarget().y,
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY(),
					16, 16)) {
					HIT = true;
					//Checking the tile types in order to change the tiles to boulders/poison
					if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
						[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] == 1) {
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
							[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] = 3;
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
							[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() + 64) / 64] = 3;
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() + 64) / 64]
							[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] = 3;
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() + 64) / 64]
							[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() + 64) / 64] = 3;

					}
					else {
						if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
							[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] != 3) {
							model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
								[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] = 1;
							model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY()) / 64]
								[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() + 64) / 64] = 1;
							model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() + 64) / 64]
								[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX()) / 64] = 1;
							model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() + 64) / 64]
								[(int)(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() + 64) / 64] = 1;
						}
					}
					view->createmapArray(view->getmapArray(), view->getStates());
				}
			}
			if (HIT ||
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() > 36 * 64 ||//did it pass the boundries?
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosX() < 0 ||
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() > 20 * 64 ||//THIS NEEDS TO BE CHANGED TO BE BASED ON currentAREA'S MAPROW/COL
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]->getPosY() < 0) {
				delete(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles()[j]);
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles().erase(
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[i]->getProjectiles().begin() + j);
			}
		}
	}
	for (unsigned j = 0; j < model->getCreatures()[0]->getProjectiles().size(); j++) {//looping over each creature's projectile vector
		//has a target been set yet? is the enemy vector empty?
		if (model->getCreatures()[0]->getID() == "spider") {
			if (model->getCreatures()[0]->getProjectiles()[j]->getState() == -1 &&
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size()>0) {
				//set target
				model->getCreatures()[0]->getProjectiles()[j]->setTarget(sf::Vector2f(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[0]->getPosX(),
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[0]->getPosY()));
				model->getCreatures()[0]->getProjectiles()[j]->setState(0);

			}
		}else if (model->getCreatures()[0]->getID() == "tank") {
			if (model->getCreatures()[0]->getProjectiles()[j]->getState() == -1) {
				//set target
				model->getCreatures()[0]->getProjectiles()[j]->setTarget(sf::Vector2f((model->getMousePos().x + model->getGuys()[0]->getPosX() - view->width / 2), 
					(model->getMousePos().y + model->getGuys()[0]->getPosY() - view->height / 2)));
				model->getCreatures()[0]->getProjectiles()[j]->setState(0);
			}
		}
		else {

		}
		model->getCreatures()[0]->getProjectiles()[j]->update(0);
		//cout << model->getCreatures()[i]->getProjectiles().size() << endl;
		bool HIT = false;
		for (unsigned k = 0; k < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies().size(); k++) {
			if (collision(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getPosX(),//did the bullet hit an enemy?
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getPosY(),
				model->getCreatures()[0]->getProjectiles()[j]->getPosX(),
				model->getCreatures()[0]->getProjectiles()[j]->getPosY(),
				16, 16)) {
				model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->setHealth(
					model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getEnemies()[k]->getHealth() - 10);//enemy loses health
				HIT = true;
				break;
			}	
		}
		if(HIT ||
			model->getCreatures()[0]->getProjectiles()[j]->getPosX() > 36 * 64 ||//did it pass the boundries?
			model->getCreatures()[0]->getProjectiles()[j]->getPosX() < 0 ||
			model->getCreatures()[0]->getProjectiles()[j]->getPosY() > 20 * 64 ||//THIS NEEDS TO BE CHANGED TO BE BASED ON currentAREA'S MAPROW/COL
			model->getCreatures()[0]->getProjectiles()[j]->getPosY() < 0||
			model->getCreatures()[0]->getProjectiles()[j]->getSpeed()<=0) {
				delete(model->getCreatures()[0]->getProjectiles()[j]);
				model->getCreatures()[0]->getProjectiles().erase(model->getCreatures()[0]->getProjectiles().begin() + j);
		}
	}
	if (model->getGuys()[0]->getBossKills() >= 2) {
		view->win();
		//model->setPause(true);
	}
}

void Controller::inputs() {
	sf::Event event;
	while (view->getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			view->getWindow().close();
			break;
		}
	}
	if (model->getGuys()[0]->getHealth() <= 0) {
		view->death();
		model->setState(model->getTypes().PAUSE);
		model->setPause(true);
	}
	timers[0]++;
	timers[1]++;
	timers[2]++;
	timers[3]++;
	int changeSprite = 0;

	if (model->getState() != model->getTypes().PAUSE) {
		if (model->getGuys()[0]->getState() == -2) {
			if (model->getCreatures()[0]->getID() == "spider") {
				sc->inputs();
			}
			else if (model->getCreatures()[0]->getID() == "tank") {
				tc->inputs();
			}
			else if (model->getCreatures()[0]->getID() == "ant") {
				ac->inputs();
			}
		}
		else {
			gc->inputs();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {//Spacebar for area's creatures
		if (view->getShowInventory() == false) {
			if (spaceTimer > 15) {
				if (collision(model->getGuys()[0]->getPosX(),
					model->getGuys()[0]->getPosY(),
					model->getCreatures()[0]->getPosX(),
					model->getCreatures()[0]->getPosY(),
					64, model->getCreatures()[0]->getSize())) {
					if (model->getGuys()[0]->getState() != -2) {//if player state is not riding								  
						model->getGuys()[0]->setState(-2);//set player state to riding
						model->getCreatures()[0]->setState(-2);//set creature state to riding MODEL's
						model->getGuys()[0]->setSize(model->getCreatures()[0]->getSize());
					}
					else {//the player state IS riding							   
						model->getGuys()[0]->setState(-3);//set player state to normal
						model->getCreatures()[0]->setState(-1);//set creature state to follow MODEL's
					}
				}
				spaceTimer = 0;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (view->getShowInventory() == false) {
			for (unsigned i = 0; i < model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem().size(); i++) {
				if (model->getGuys()[0]->getItemCount() < model->getGuys()[0]->getInventorySize()) {
					if (collision(model->getGuy().getPosX(),//Did the player and the item collide?
						model->getGuy().getPosY(),
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY(),
						64, 64)) {
						Item* newItem;
						if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Weapon") { //Is it a weapon?
							newItem = new Weapon(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getValue(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getDamage(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
						}
						else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Armour") { //Is it armour?
							newItem = new Armour(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getValue(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getDefense(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
						}
						else if (model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType() == "Creature Egg") { //Is it armour?
							newItem = new CreatureStone(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getName(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getValue(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getType(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosX(),
								model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]->getPosY());
						}
						else {
							newItem = new Weapon;
						}
						model->getGuys()[0]->addItem(newItem);//Add the 'copy' to the guy's inventory
						delete(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem()[i]);//Delete the item on the map
						model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem().erase(
							model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getMapItem().begin() + i);//Remove it from the mapItem vector
					}
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		if (timers[1] > 30) {
			if (view->getShowInventory() == true) {
				view->setShowInventory(false);
				model->setState(model->getTypes().PLAYING);
			}
			else {
				model->getGuys()[0]->setSelectedItem(0);
				view->setShowInventory(true);
				model->setState(model->getTypes().PAUSE);
			}
			timers[1] = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (timers[0] > 5) {
			model->getGuys()[0]->setSelectedItem(model->getGuys()[0]->getSelectedItem() + 1);
			if (model->getGuys()[0]->getSelectedItem() >14) {
				model->getGuys()[0]->setSelectedItem(0);
			}
			timers[0] = 0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		//deleteh item
		if (timers[3] >= 30) {
			if (view->getShowInventory() == true && model->getGuys()[0]->getInventory().size() > model->getGuys()[0]->getSelectedItem() &&
				model->getGuys()[0]->getInventory().size() > 0) {
				model->getGuys()[0]->deleteItem(model->getGuys()[0]->getSelectedItem());
			}
			timers[3] = 0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (timers[2] >= 30) {
			//Checks to see if inventory is open, and that the item count is >= the index of the selected item and that the item count is > 0
			if (view->getShowInventory() == true && model->getGuys()[0]->getInventory().size() > model->getGuys()[0]->getSelectedItem() &&
				model->getGuys()[0]->getInventory().size() > 0) {
				if (model->getGuys()[0]->getState()!=-2) {
					if (model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]->getName() == "Spider Egg") {
						Spider *s = new Spider;
						s->setPosX(model->getCreatures()[0]->getPosX());
						s->setPosY(model->getCreatures()[0]->getPosY());
						model->getCreatures().clear();
						model->getCreatures().push_back(s);
					}
					else if (model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]->getName() == "Little Egg") {
						Ant *a = new Ant;
						a->setPosX(model->getCreatures()[0]->getPosX());
						a->setPosY(model->getCreatures()[0]->getPosY());
						model->getCreatures().clear();
						model->getCreatures().push_back(a);
					}
					else if (model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]->getName() == "Tank Egg") {
						Tank *t = new Tank;
						t->setPosX(model->getCreatures()[0]->getPosX());
						t->setPosY(model->getCreatures()[0]->getPosY());
						model->getCreatures().clear();
						model->getCreatures().push_back(t);
					}
					model->getGuys()[0]->useItem(model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]);
				}
				else {
					if (model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]->getType() != "Creature Egg") {
						model->getGuys()[0]->useItem(model->getGuys()[0]->getInventory()[model->getGuys()[0]->getSelectedItem()]);
					}
				}
			}
			timers[2] = 0;
		}
		if (model->getState() == model->getTypes().TITLE) {
			model->setState(model->getTypes().PLAYING);
		}
	}
}

bool Controller::collision(float x1, float y1, float x2, float y2, int size1, int size2) {
	float radius1 = 0.75 * size1;
	float radius2 = 0.75 * size2;

	float dx = x2 - x1;
	float dy = y2 - y1;
	float dist = (dx*dx) + (dy*dy);

	if (dist < ((radius1 + radius2)*(radius1 + radius2))) {
		sf::FloatRect p_rect(x1, y1, size1, size1);
		sf::FloatRect c_rect(x2, y2, size2, size2);
		sf::FloatRect result;
		return p_rect.intersects(c_rect, result);
	}
	return false;
}