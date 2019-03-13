#include "AntController.h"



AntController::AntController(Model* m, View* v) {
	model = m;
	view = v;
}

AntController::AntController()
{
}

AntController::~AntController()
{
}

void AntController::inputs() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() + 0.025);
		view->rotateCreature(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() - 0.025);
		view->rotateCreature(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getCreatures()[0]->getPosY() - cos(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)]
			[(int)round((model->getCreatures()[0]->getPosX() + sin(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)] <model->getBarrierN())) {
		}
		else {
			model->getCreatures()[0]->ride();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

	}
}
