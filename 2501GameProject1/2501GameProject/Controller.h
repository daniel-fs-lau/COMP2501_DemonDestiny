#pragma once
#include "Model.h"
#include "View.h"
#include "GuyController.h"
#include "SpiderController.h"
#include "TankController.h"
#include "AntController.h"

class Controller {
	Model* model;
	View* view;
	GuyController* gc;
	SpiderController* sc;
	TankController* tc;
	AntController* ac;
	int frames;
	int target;
	int direction;
	int timer,spaceTimer;
	int timers[10];
public:
	vector<Enemy*>::iterator it;
	Controller();
	Controller(Model* m, View* v);
	~Controller();

	void update(float);
	void inputs();
	bool collision(float x1, float y1, float x2, float y2, int size1,int size2);

};