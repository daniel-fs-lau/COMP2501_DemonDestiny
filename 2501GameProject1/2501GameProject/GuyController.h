#pragma once

#include "Model.h"
#include "View.h"
class GuyController
{
	Model* model;
	View* view;
	int frames;
	int target;
	int direction;
	int changeSprite;
	float angles;
	int shoot;
	int shootTimer;
public:
	GuyController();
	GuyController(Model* m, View* v);
	~GuyController();
	void switchArea();
	void inputs();
	void updatePlayerSprite();
	void updatePlayerDirection();
	int  getChangeSprite();
	void setChangeSprite(int);
};