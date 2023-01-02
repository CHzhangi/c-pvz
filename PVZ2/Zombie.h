#pragma once
#pragma once
#include"config.h"
using namespace std;
#include<string.h>
#include <vector>

class Zombie
{
protected:
	string ZOMBIE_ID; //名字
	int x, y; //坐标
	int maxhp; //僵尸满血血量
	int ATK; //攻击力
	int AS; //攻速
	int MS; //移速
	int color; 
	int current_hp; //僵尸当前血量
	bool valid; //是否存活
	int eat_count;
	int move_count; //移动状态技术
	int bonus;//击败可以获得的奖励
public:
	void set_parm(string a, int hp, int atk, int as, int ms, int dx, int dy)
	{
		ZOMBIE_ID = a;
		current_hp=maxhp = hp;
		ATK = atk;
		AS = as;
		MS = ms;
		x = dx;
		y = dy;
		valid = 1;
		move_count = 2;
		eat_count = 50;
		bonus = 20;
	}
	Zombie() {};
	bool beHit(int atk);
	int get_x() const;
	int get_y() const;

	string get_ID();
	bool isValid() const;
	void move();
	friend void showZombie(const Zombie& zombie);
	friend void cleanZombie(const Zombie& zombie);
};

class ZombieList
{
private:
	std::vector<Zombie*> zombie_list;
	int create_count;
	int create_time;
	int creat_status;
public:
	ZombieList();
	void addZombie();
	void zombiedoing();
	Zombie* getZombie(int x, int y);
	std::vector<Zombie*> getZombie(int r);
};

class normalzombie : public Zombie
{
public:
	normalzombie(int x, int y)
	{
		set_parm("普通僵尸", 500, 80, 20, 20, x, y);
	}
};


