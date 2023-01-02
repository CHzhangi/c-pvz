#include"globalv.h"
#include<list>
#include<iostream>
using namespace std;
int  Zombie::get_x() const
{
	return x;
}

int  Zombie::get_y() const
{
	return y;
}

string Zombie::get_ID()
{
	return ZOMBIE_ID;
}
bool Zombie::beHit(int atk)
{
	current_hp -= atk;
	color=YELLOW;
	valid = (current_hp > 0);
	if (valid == 0)
	{
		sunlight+=this->bonus;//获得奖励
	}
	return valid;
}

bool Zombie::isValid() const
{
	return valid;
}

void Zombie::move()
{
	if (move_count >= MS)
	{
		int dy = (y - TOP_HIGH) / (ROW_HIGH + 1);
		int dx = x / (COL_WIDTH + 1);
		Plant* plant = plantlist.getPlant(dx, dy);
		if (plant == NULL)
		{
			// 移动
			x--;
			if (x == -1)
				alive = 0;
		}
		move_count = 0;
		eat_count++;
	}
	else if (eat_count >= AS)
	{
		int dy = (y - TOP_HIGH) / (ROW_HIGH + 1);
		int dx = x / (COL_WIDTH + 1);
		Plant* plant = plantlist.getPlant(dx, dy);
		if (plant != NULL)
		{
			plant->beingEaten(ATK);				
		}		
		eat_count = 0;
		move_count+=10;
	}
	else
	{
		// 等待
		move_count++;
		eat_count++;
		Plant* tmp = NULL;
	}
	return;
}
ZombieList::ZombieList()
{
	create_count = 0;
	creat_status = 0;
	create_time = FIRST_ZOMBIE_TIME;
}
Zombie* ZombieList::getZombie(int x, int y)
{
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end(); i++)
	{
		if (abs((*i)->get_x()-x)<3 && (*i)->get_y() == y)
			return *i;
	}
	return NULL;
}

void ZombieList::addZombie()
{
	int temp = 0;
	int r = rand() % ROW;
	int y = r * (ROW_HIGH + 1) + TOP_HIGH;
	for (int i = 0; i < 5; i++)//基础版不允许僵尸重叠影响视觉
	{
		if (zombielist.getZombie(NEW_ZOMBIE_X, y))
		{
			temp = -1; // 不产生僵尸
		}
	}
	if (temp != -1)
	{
		Zombie* zombie = new normalzombie(NEW_ZOMBIE_X, y);
		zombie_list.push_back(zombie);
	}
}

void ZombieList::zombiedoing()
{
	for (std::vector<Zombie*>::iterator i = zombie_list.begin();
		i != zombie_list.end();)
	{
		if ((*i)->isValid())
		{
			(*i)->move();
			showZombie(*(*i));
			i++;
		}
		else
		{
			cleanZombie(**i);
			delete (*i);
			i = zombie_list.erase(i);
		}
	}
	if (create_count > create_time)
		creat_status = 1;
	if (creat_status == 0 || create_count < create_time)
	{
		create_count++;
	}
	else
	{
		create_count = create_count - rand() % 800;
		addZombie();
	}
}
std::vector<Zombie*> ZombieList::getZombie(int r)
{
	int y = r * (ROW_HIGH + 1) + TOP_HIGH;
	std::vector<Zombie*> zombies;
	for (std::vector<Zombie*>::iterator itor = zombie_list.begin();
		itor != zombie_list.end(); itor++)
	{
		if ((*itor)->get_y() == y)
			zombies.push_back(*itor);
	}
	return zombies;
}