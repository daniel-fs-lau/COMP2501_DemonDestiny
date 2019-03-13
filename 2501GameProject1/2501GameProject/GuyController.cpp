#include "GuyController.h"



GuyController::GuyController(Model* m, View* v)
{
	model = m;
	view = v;
	frames = 0;
	target = 15;
	direction = 2;
	changeSprite = 0;
	shoot = 0;
	shootTimer = 0;
}


GuyController::~GuyController()
{
}

void GuyController::switchArea() {
	if (model->getGuys()[0]->getPosX() > model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64 ||
		model->getCreatures()[0]->getPosX() > model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64) {
		if (model->getcurrentSubArea() == 0) {
			if (model->getcurrentArea() == 0) {
				model->setcurrentArea(2);
				model->getGuys()[0]->setPosX(0);
				model->getCreatures()[0]->setPosX(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() != 4) {
				model->setcurrentSubArea(2);
				model->getGuys()[0]->setPosX(0);
				model->getCreatures()[0]->setPosX(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() == 4) {
				model->setcurrentArea(0);
				model->getGuys()[0]->setPosX(0);
				model->getCreatures()[0]->setPosX(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
		}
		else if (model->getcurrentSubArea() == 4) {
			model->setcurrentSubArea(0);
			model->getGuys()[0]->setPosX(0);
			model->getCreatures()[0]->setPosX(0);
			view->setFloor(model->getcurrentArea());
			view->createmapArray(view->getmapArray(), view->getStates());
		}
	}
	else if (model->getGuys()[0]->getPosX() < 0 || model->getCreatures()[0]->getPosX() < 0) {
		if (model->getcurrentSubArea() == 0) {

			if (model->getcurrentArea() == 0) {
				model->setcurrentArea(4);
				model->getGuys()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				model->getCreatures()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() != 2) {
				model->setcurrentSubArea(4);
				model->getGuys()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				model->getCreatures()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() == 2) {
				model->setcurrentArea(0);
				model->getGuys()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				model->getCreatures()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
		}
		else if (model->getcurrentSubArea() == 2) {
			model->setcurrentSubArea(0);
			model->getGuys()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
			model->getCreatures()[0]->setPosX(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapCols() * 64 - 64);
			view->setFloor(model->getcurrentArea());
			view->createmapArray(view->getmapArray(), view->getStates());
		}
	}
	else if (model->getGuys()[0]->getPosY() < 0 || model->getCreatures()[0]->getPosY() < 0) {
		if (model->getcurrentSubArea() == 0) {

			if (model->getcurrentArea() == 0) {
				model->setcurrentArea(1);
				model->getGuys()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				model->getCreatures()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() != 3) {
				model->setcurrentSubArea(1);
				model->getGuys()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				model->getCreatures()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() == 3) {
				model->setcurrentArea(0);
				model->getGuys()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				model->getCreatures()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
		}
		else if (model->getcurrentSubArea() == 3) {
			model->setcurrentSubArea(0);
			model->getGuys()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
			model->getCreatures()[0]->setPosY(model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64);
			view->setFloor(model->getcurrentArea());
			view->createmapArray(view->getmapArray(), view->getStates());
		}
	}
	else if (model->getGuys()[0]->getPosY() > model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64 ||
		model->getCreatures()[0]->getPosY() > model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->getmapRows() * 64 - 64) {
		if (model->getcurrentSubArea() == 0) {
			if (model->getcurrentArea() == 0) {
				model->setcurrentArea(3);
				model->getGuys()[0]->setPosY(0);
				model->getCreatures()[0]->setPosY(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() != 1) {
				model->setcurrentSubArea(3);
				model->getGuys()[0]->setPosY(0);
				model->getCreatures()[0]->setPosY(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
			else if (model->getcurrentArea() == 1) {
				model->setcurrentArea(0);
				model->getGuys()[0]->setPosY(0);
				model->getCreatures()[0]->setPosY(0);
				view->setFloor(model->getcurrentArea());
				view->createmapArray(view->getmapArray(), view->getStates());
			}
		}
		else if (model->getcurrentSubArea() == 1) {
			model->setcurrentSubArea(0);
			model->getGuys()[0]->setPosY(0);
			model->getCreatures()[0]->setPosY(0);
			view->setFloor(model->getcurrentArea());
			view->createmapArray(view->getmapArray(), view->getStates());
		}
	}
}


void GuyController::inputs() {

	angles = -(atan2(model->getMousePos().y - (view->height/2 + 32), model->getMousePos().x - (view->width/2 + 32)) * 57.296f);
	frames++;
	shootTimer++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		changeSprite = 0;
		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getGuys()[0]->getPosY()) / 64)]
			[(int)round((model->getGuys()[0]->getPosX() + model->getGuys()[0]->getSpeed()) / 64)] < model->getBarrierN())) {
		}
		else {
			model->getGuys()[0]->setPosX(model->getGuys()[0]->getPosX() + model->getGuys()[0]->getSpeed());
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		frames++;
		changeSprite = 0;

		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getGuys()[0]->getPosY()) / 64)]
			[(int)round((model->getGuys()[0]->getPosX() -model->getGuys()[0]->getSpeed()) / 64)] < model->getBarrierN())) {
		}
		else {
			model->getGuys()[0]->setPosX(model->getGuys()[0]->getPosX() - model->getGuys()[0]->getSpeed());
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		changeSprite = 0;

		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getGuys()[0]->getPosY() - model->getGuys()[0]->getSpeed()) / 64)]
			[(int)round((model->getGuys()[0]->getPosX()) / 64)] < model->getBarrierN())) {
		}
		else {
			model->getGuys()[0]->setPosY(model->getGuys()[0]->getPosY() - model->getGuys()[0]->getSpeed());
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		changeSprite = 0;
		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getGuys()[0]->getPosY() + model->getGuys()[0]->getSpeed()) / 64)]
			[(int)round((model->getGuys()[0]->getPosX()) / 64)] < model->getBarrierN())) {
		}
		else {
			model->getGuys()[0]->setPosY(model->getGuys()[0]->getPosY() + model->getGuys()[0]->getSpeed());
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (shootTimer > 30) {
			shoot = 1;
			shootTimer = 0;
		}
	}

	updatePlayerSprite();
	updatePlayerDirection();

}

void GuyController::updatePlayerSprite() {
	if (changeSprite == 0 && frames >= target) {//Changing the texture to load onto the sprite(numbers corresspond to texture on spritesheet
		if (model->getSprite() % 2 == 0) {
			model->setSprite(1);
		}
		else {
			model->setSprite(0);
		}

		changeSprite = 1;
		frames = 0;
	}
}
void GuyController::updatePlayerDirection() {
	if (angles <= 45 && angles >-45) {

		if (model->getSprite() % 2 == 0) {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 12, model->getGuys()[0]->getPosY() + 10, 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(6);
		}
		else {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 18, model->getGuys()[0]->getPosY() + 8, 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(7);
		}
	}
	else  if (angles <= 135 && angles > 45) {
		if (model->getSprite() % 2 == 0) {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 46, model->getGuys()[0]->getPosY() + 4, 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(0);
		}
		else {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 50, model->getGuys()[0]->getPosY() + 8, 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(1);
		}
	}
	else  if (angles <= -45 && angles >= -135) {
		if (model->getSprite() % 2 == 0) {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 12, model->getGuys()[0]->getPosY() - 12, 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(4);
		}
		else {
			if (shoot == 1) {
				Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 2, model->getGuys()[0]->getPosY(), 0, 0, -1, 10, -1, -1);
				model->getGuys()[0]->getProjectiles().push_back(p);
				shoot = 0;
			}
			model->setSprite(3);
		}
	}
	else  if (abs(angles)>135) {
		if (shoot == 1) {
			Projectile* p = new Bullet(model->getGuys()[0]->getPosX() + 10, model->getGuys()[0]->getPosY() + 4, 0, 0, -1, 10, -1, -1);
			model->getGuys()[0]->getProjectiles().push_back(p);
			shoot = 0;
		}
		if (model->getSprite() % 2 == 0) {
			model->setSprite(2);
		}
		else {
			model->setSprite(5);
		}
	}
}


int  GuyController::getChangeSprite() {
	return changeSprite;
}
void GuyController::setChangeSprite(int c) {
	changeSprite = c;
}