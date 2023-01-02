#pragma once
#pragma once
#include"config.h"
using namespace std;
#include<string.h>
#include <vector>

class Zombie
{
protected:
	string ZOMBIE_ID; //����
	int x, y; //����
	int maxhp; //��ʬ��ѪѪ��
	int ATK; //������
	int AS; //����
	int MS; //����
	int color; 
	int current_hp; //��ʬ��ǰѪ��
	bool valid; //�Ƿ���
	int eat_count;
	int move_count; //�ƶ�״̬����
	int bonus;//���ܿ��Ի�õĽ���
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
		set_parm("��ͨ��ʬ", 500, 80, 20, 20, x, y);
	}
};


