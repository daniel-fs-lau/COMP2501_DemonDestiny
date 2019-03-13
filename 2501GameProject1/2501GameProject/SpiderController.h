#pragma once
#include "Model.h"
#include "View.h"
class SpiderController
{
	Model* model;
	View* view;
public:
	SpiderController();
	SpiderController(Model* m,View* v);
	~SpiderController();
	void inputs();
};

