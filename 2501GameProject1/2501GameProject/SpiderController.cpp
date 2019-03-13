#include "SpiderController.h"



SpiderController::SpiderController(Model* m, View* v) {
	model = m;
	view = v;
}

SpiderController::SpiderController()
{
}

SpiderController::~SpiderController()
{
}

void SpiderController::inputs() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() + 0.025);
		view->rotateCreature(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() - 0.025);
		view->rotateCreature(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getCreatures()[0]->getPosY() - cos(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)]
			[(int)round((model->getCreatures()[0]->getPosX() + sin(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)] <model->getBarrierN())) {
			model->getCreatures()[0]->ride();
			if (model->getCreatures()[0]->getPosX() < 10 || model->getCreatures()[0]->getPosX() > 2230 || model->getCreatures()[0]->getPosY() < 10 || model->getCreatures()[0]->getPosY() > 1206) {
				model->getCreatures()[0]->setPosX(model->getCreatures()[0]->getPosX() - round(sin(model->getCreatures()[0]->getAngle()) * model->getCreatures()[0]->getSpeed()));
				model->getCreatures()[0]->setPosY(model->getCreatures()[0]->getPosY() + round(cos(model->getCreatures()[0]->getAngle()) * model->getCreatures()[0]->getSpeed()));
			}
			else {

			}
		}
		else {
			model->getCreatures()[0]->ride();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

	}

}
