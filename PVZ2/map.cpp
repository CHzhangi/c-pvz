#include <math.h>
#include"globalv.h"
extern int cost[]; // 植物花费
extern int Waitime[];
extern const char* plantname_list[]; //植物名字

PlantSelector::PlantSelector()
{
	pid = 0;
}

PlantSelector::~PlantSelector()
{
	pid=0;
}

void PlantSelector::reinit()
{
	pid = 0;
}

void PlantSelector::setPlant(int pid)
{
	this->pid = pid;
}

int PlantSelector::getPlant() const
{
	return pid;
}

MapSelector::MapSelector()  {

	x = 0; y = 0;
}

MapSelector::~MapSelector()
{
	reinit();
}

void MapSelector::reinit()
{
	x = 0;
	y = 0;
}

void MapSelector::move(int direction)
{
	cleanselector();
	switch (direction)
	{
	case UP:
		y = (y + ROW - 1) % ROW;
		break;
	case LEFT:
		x = (x + COL - 1) % COL;
		break;
	case RIGHT:
		x = (x + 1) % COL;
		break;
	case DOWN:
		y = (y + 1) % ROW;
		break;
	default:;
	}
}
int MapSelector::get_x() const
{
	return x;

}
int MapSelector::get_y() const
{

	return y;
}

int Shop::buyPlant()//1:无误  0:此地已有植物 -1：冷却中 -2：未知的错误 -3：阳光不足
{
	int temp = 0;
	int pid = ps.getPlant();
	int need_sun = cost[pid];
	if (wait_time[pid] > 0)
		return -1;
	if (sunlight >= need_sun)
	{
		int x = ms.get_x();
		int y = ms.get_y();
		temp = 1;
		switch (pid)
		{
		case 0:
		{
			Sunflower* p = new Sunflower(x, y);
			if (plantlist.addPlant(p))
			{
				sunlight -= need_sun;
			}
			else
			{
				temp = 0;
				status = 2;
			}
			break;
		}
		case 1:
		{
			PeaShooter* p = new PeaShooter(x, y);
			if (plantlist.addPlant(p))
			{
				sunlight -= need_sun;
			}
			else
			{
				temp = 0;
				status = 2;
			}
			break;
		}
		default:
			temp= -2;
		}
		if (temp == 1)
			wait_time[pid] = Waitime[pid];//进入冷却
	}
	return temp;
}

Shop::Shop() :status(1)
{
	wait_time = new int[PLANT_KIND_NUM]();
}


void Shop::choosePlant()
{
	const char* name = plantname_list[ps.getPlant()];
	char msg[64] = "选中植物";
	int i = 0;
	for (i = 0; name[i] != 0; i++)
		msg[8 + i] = name[i];
	showMessage(msg);
	status = 1;
}

void Shop::unchoosePlant()//0 正在选择植物  1 选地图位置
{
	status = 1;
	showselector();
}

void Shop::mapdoing(int key)
{
	if (status == 0)
	{
		switch (key)
		{
		case NUM1:case NUM2:
			ps.setPlant(key - NUM0 - 1);
			choosePlant();
			break;
		//case ENTER:
		//	choosePlant();
		//	break;
		default:
			char msg[64] = "清先选中植物";
			showMessage(msg);
		}
	}
	else if (status == 1)
	{
		switch (key)
		{
		case UP:case DOWN:case LEFT:case RIGHT:
			ms.move(key);
			break;
		case ENTER:
		{
			int success = buyPlant();
			if (success == 0)
			{
				if (status == 2)
				{
					status = 0;
					sunlight += cost[ps.getPlant()];
					showMessage("该位置无法种植");
					cleanselector();
				}
				else
				{
					status = 0;
					showMessage("阳光不足，无法种植！");
					cleanselector();
				}
			}
			else if (success == 1)
			{
				const char* name = plantname_list[ps.getPlant()];
				char msg[64] = "成功种植！";
				int i = 0;
				for (i = 0; name[i] != 0; i++)
					msg[8 + i] = name[i];
				msg[8 + i] = '!';
				showMessage(msg);
				unchoosePlant();
			}
			else if (success == -1)
			{
				status = 0;
				showMessage("植物还在冷却！无法种植");
				cleanselector();
			}
			else if (success == -2)
			{
				status = 0;
				showMessage("没有这种植物！");
				cleanselector();
			}
			break;
		}
		case NUM1:case NUM2:
			ps.setPlant(key - NUM0 - 1);
			choosePlant();
			status = 1;
			break;
		default:;
		}
	}
}

void Shop::wait()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
		if (wait_time[i] > 0)
			wait_time[i]--;
}
