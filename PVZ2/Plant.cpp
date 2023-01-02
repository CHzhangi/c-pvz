#include"globalv.h"
#include<list>
#include<iostream>
using namespace std;
int cost[] = { 50, 100 };
int Waitime[] = { 50, 50 };
const char* plantname_list[] = { "向日葵", "豌豆射手" };
bool Plant::beingEaten(int atk)
{
	current_hp -= atk;
	if (current_hp <= 0)
	{
		valid = 0;
		return false;
	}
	else
	{
		valid = 1;
		return true;
	}
}

int  Plant::get_x() const
{
	return x;
}

int  Plant::get_y() const
{
	return y;
}
string Plant::getID() const
{
	return plant_id;
}

bool Plant::ifValid() const
{
	return valid;
}


PlantList::PlantList() {}

bool PlantList::addPlant(Plant* plant)
{
	Plant* i;
	list<Plant*>::iterator itor;
	itor = plant_list.begin();
	if (plant_list.empty())
	{
		plant_list.push_front(plant);
		return true;
	}
	while (itor != plant_list.end()) {
		if ((*itor)->get_x() == plant->get_x() && (*itor)->get_y() == plant->get_y())
			return false;
		itor++;

	}
	plant_list.push_front(plant);
	return true;
}

void PlantList::plantsdoing()
{
	list<Plant*>::iterator itor;
	itor = plant_list.begin();
	while (itor != plant_list.end()) {
		if ((*itor)->ifValid())
		{
			(*itor)->hit();
			showPlant(*(*itor));
			itor++;
		}
		else
		{
			cleanPlant(*(*itor));
			plant_list.erase(itor++);
		}
	}
	
}


Plant* PlantList::getPlant(int r, int c)
{
	list<Plant*>::iterator itor;
	itor = plant_list.begin();
	while (itor != plant_list.end()) {
		if ((*itor)->get_x() ==r && (*itor)->get_y() ==c)
			return (*itor);
		itor++;

	}
	return NULL;
}


void Sunflower::hit()
{
	if (status_count >= AS)
	{
		sunlight += ATK;
		color = RED;//产生阳光时一个ui信息
		status_count = 0;
	}
	else
	{
		status_count++;
		color = YELLOW;
	}
	return;
}

void PeaShooter::hit()
{
	if (status_count >= AS)
	{
		int dx = (x + 1) * (COL_WIDTH + 1) - 1;
		int dy = y * (ROW_HIGH + 1) + TOP_HIGH + ROW_HIGH / 2;
		auto zombies = zombielist.getZombie(y);
		for (auto z : zombies)
		{
			if (z->get_x() >= dx)
			{				// 发出子弹
				Bullet* blt = new Bullet(dx, dy);
				bulletlist.addBullet(blt);
				status_count = 0;
				break;
			}
		}
	}
	else		
		status_count++;
	return;
}

