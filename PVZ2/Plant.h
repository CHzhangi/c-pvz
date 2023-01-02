#pragma once
#include "config.h"
#include<string.h>
#include<iostream>
#include<utility>
#include<list>
using namespace std;
class Plant
{
protected:
	string plant_id; 
	int x, y;
	int maxhp; 
	int ATK; 
	int AS; 
	int color; 
	int current_hp; 
	bool valid; 
	int status_count; //攻击状态计数,达到AS才能攻击
public:
	//构造函数，提供植物类型和坐标
	void setparm(string name, int dx, int dy, int hp, int atk, int color_,int as)
	{
		plant_id = name;
		x = dx;
		y = dy;
		maxhp = current_hp = hp;
		color = color_;
		AS = as;
		status_count = 5;
		ATK = atk;
	}
	Plant(){}
	bool beingEaten(int atk);
	int get_x() const;
	int get_y() const;
	string getID() const;
	bool ifValid() const;
	virtual void hit() = 0;
	friend void showPlant(const Plant& plant);
	friend void cleanPlant(const Plant& plant);
};

class PlantList
{
private:
	list<Plant*>plant_list;
public:
	PlantList();
	bool addPlant(Plant* plant);
	void plantsdoing();
	Plant* getPlant(int r, int c);
};

class Sunflower : public Plant
{
public:
	Sunflower(int dx,int dy)
	{
		setparm("sunflower", dx, dy, 300, 50,YELLOW,100);
	}
	void hit();//不同的是，该函数用于向日葵产生太阳
};

class PeaShooter : public Plant
{
public:
	// 构造函数，传递行列号
	PeaShooter(int dx, int dy)
	{
		setparm("peashooter", dx, dy, 500, 100, GREEN,20);

	}
	// 攻击函数
	void hit();
};
