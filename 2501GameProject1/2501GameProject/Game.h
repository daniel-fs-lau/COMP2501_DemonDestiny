#pragma once
#include "View.h"
#include "Model.h"
#include "Controller.h"

class Game {

	Model* model = new Model();
	View* view;
	Controller* controller;
public:
	Game();
	~Game();
	void loop();
	void inputs();
	void update(float);
	void render();

};