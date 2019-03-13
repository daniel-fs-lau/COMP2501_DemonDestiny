#pragma once
#include "Model.h"
#include "View.h"
class AntController
{
	Model* model;
	View* view;
public:
	AntController();
	AntController(Model* m, View* v);
	~AntController();
	void inputs();
};

