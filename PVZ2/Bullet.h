#pragma once
#include"config.h"
#include<vector>
#include<iostream>
using namespace std;
class Bullet {

	int x;
	int y;
	int speed;
	int atk;
	bool valid;
	int color;
	int status_count;
public:
	void set_parm(int dx, int dy, int SPEED, int ATK, int color_)
	{
		x = dx;
		y = dy;
		speed = SPEED;
		atk = ATK;
		color = color_;
		status_count = 4;
	}
	Bullet(int dx,int dy)
	{
		set_parm(dx, dy, 1, 10, GREEN);
		status_count = 0;
	}
	bool move_or_disappaer();
	int get_x() const;
	int get_y() const;
	friend void showBullet(const Bullet& blt);
};

class BulletList
{
private:
	std::vector<Bullet*> bullet_list;
public:
	BulletList();
	~BulletList();
	void addBullet(Bullet* blt);// Ìí¼Ó×Óµ¯
	void bulletdoing();// OPeration on bullet class
};








