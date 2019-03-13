#include "Game.h"


Game::Game() {
	view = new View(model);
	controller = new  Controller(model, view);
}

Game::~Game() {

}

void Game::loop() {
	while (view->getWindow().isOpen())
	{
		//Some frame limiting should go here. You should use some sf::Time variable that tracks deltaTime, and then pass that to update. Fix your update agrument
		//type to take sf::Timed
		//cout << model->getplayerX() << "\n";
		inputs();
		if (model->getState() == model->getTypes().PLAYING){
			update(0);
		}
		render();
	}
}

//checks for input func
void Game::inputs() {
	//if(!model->getPause())
	controller->inputs();
}

void Game::render() {
	view->render();
}

void Game::update(float deltaTime) {
//	if (!model->getPause())
	controller->update(deltaTime);
}