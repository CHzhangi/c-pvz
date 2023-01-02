#include "globalv.h"
bool Bullet::move_or_disappaer()
{
	if (status_count >= speed)
	{
		int dx = x - 1;
		int dy = y - ROW_HIGH / 2;
		int i = 0;
		x++;
		Zombie* zombie = zombielist.getZombie(dx, dy);
		if (zombie == NULL)
		{
			status_count = 0;
			if (x >= WINDOWS_WIDTH - 1)
				valid = 0;
		}
		else
		{
			zombie->beHit(atk);
			valid = 0;
		}
	}
	else
		status_count++;
	return valid;
}


int Bullet::get_x()const
{
	return x;

}
int Bullet::get_y() const
{
	return y;
}
BulletList::BulletList() {}

BulletList::~BulletList()
{}

void BulletList::addBullet(Bullet* blt)
{
	bullet_list.push_back(blt);
}

void BulletList::bulletdoing()
{
	for (std::vector<Bullet*>::iterator itor = bullet_list.begin();
		itor != bullet_list.end();)
	{
		if ((*itor)->move_or_disappaer())
		{
			showBullet(**itor);
			itor++;
		}
		else
		{
			cleanBullet(**itor);
			delete (*itor);
			itor = bullet_list.erase(itor);
		}
	}
}
