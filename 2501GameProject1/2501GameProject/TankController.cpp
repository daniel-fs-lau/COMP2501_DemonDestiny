#include "TankController.h"

TankController::TankController(Model* m, View* v) {
	model = m;
	view = v;
}

TankController::TankController()
{
}

TankController::~TankController()
{
}

void TankController::inputs() {
	sf::Event event2;
	while (view->getWindow().pollEvent(event2))
	{
		switch (event2.type)
		{
		case sf::Event::Closed:
			view->getWindow().close();
			break;
		case sf::Event::MouseButtonPressed:
			cout << "clicked";
			model->getCreatures()[0]->setCharging(true);
			break;
		case sf::Event::MouseButtonReleased:
			cout << "Released";
			model->getCreatures()[0]->setCharging(false);
			model->getCreatures()[0]->shoot();
			break;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() + 0.025);
		view->rotateCreature(1);
		model->getCreatures()[0]->setSpeed(0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		model->getCreatures()[0]->setAngle(model->getCreatures()[0]->getAngle() - 0.025);
		view->rotateCreature(1);
		model->getCreatures()[0]->setSpeed(0.1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if ((model->getAreas()[model->getcurrentArea()][model->getcurrentSubArea()]->mapData[(int)round((model->getCreatures()[0]->getPosY() - cos(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)]
			[(int)round((model->getCreatures()[0]->getPosX() + sin(model->getCreatures()[0]->getAngle())*model->getCreatures()[0]->getSpeed()) / 64)] <model->getBarrierN())) {
			//model->getCreatures()[0]->ride();
		}
		else {
			if (model->getCreatures()[0]->getSpeed() < 5) {
				model->getCreatures()[0]->setSpeed(model->getCreatures()[0]->getSpeed() + 0.03);
			}
			else if (model->getCreatures()[0]->getSpeed() < 20) {
				model->getCreatures()[0]->setSpeed(model->getCreatures()[0]->getSpeed() + 0.05);
			}
			model->getCreatures()[0]->ride();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

	}

}