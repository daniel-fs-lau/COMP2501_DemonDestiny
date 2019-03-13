#pragma once
#include "Model.h"
#include "View.h"
class TankController
{
	Model* model;
	View* view;
public:
	TankController();
	TankController(Model* m, View* v);
	~TankController();
	void inputs();
};

