#pragma once
#include <string>

using namespace std;

class Item
{
protected:
	string name;
	string type;
	int damage;
	int defense;
	int value;
	int itemX;
	int itemY;

public:
	Item();
	Item(string, int, string, int, int);
	Item(Item&);
	~Item();
	std::string getName();
	std::string getType();
	virtual int getDamage();
	virtual int getDefense();
	int getPosX();
	int getPosY();
	void setPosX(int);
	void setPosY(int);
	int getValue();
	void setValue(int);
	//Item* makeCopy(Item*);
};

