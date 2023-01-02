#include <math.h>
#include"globalv.h"
extern int cost[]; // ֲ�ﻨ��
extern int Waitime[];
extern const char* plantname_list[]; //ֲ������

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

int Shop::buyPlant()//1:����  0:�˵�����ֲ�� -1����ȴ�� -2��δ֪�Ĵ��� -3�����ⲻ��
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
			wait_time[pid] = Waitime[pid];//������ȴ
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
	char msg[64] = "ѡ��ֲ��";
	int i = 0;
	for (i = 0; name[i] != 0; i++)
		msg[8 + i] = name[i];
	showMessage(msg);
	status = 1;
}

void Shop::unchoosePlant()//0 ����ѡ��ֲ��  1 ѡ��ͼλ��
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
			char msg[64] = "����ѡ��ֲ��";
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
					showMessage("��λ���޷���ֲ");
					cleanselector();
				}
				else
				{
					status = 0;
					showMessage("���ⲻ�㣬�޷���ֲ��");
					cleanselector();
				}
			}
			else if (success == 1)
			{
				const char* name = plantname_list[ps.getPlant()];
				char msg[64] = "�ɹ���ֲ��";
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
				showMessage("ֲ�ﻹ����ȴ���޷���ֲ");
				cleanselector();
			}
			else if (success == -2)
			{
				status = 0;
				showMessage("û������ֲ�");
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
