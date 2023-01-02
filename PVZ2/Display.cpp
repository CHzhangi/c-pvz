#include "globalv.h"
#include <stdio.h>
#include <string.h>
#include <math.h> 
#include<iostream>
using namespace std;

extern const char* plantname_list[]; // 植物名字
extern int cost[];
extern int Waitime[];
extern const char* _MENU_NAME[];
void showImg()
{
	setCursorPos(WINDOWS_WIDTH / 2 - 8, WINDOWS_HIGH / 2 - 6);
	setColor(YELLOW);
	printf("欢迎来到");
	setCursorPos(WINDOWS_WIDTH / 2 - 18, WINDOWS_HIGH / 2);
	setColor(GREEN);
	printf("plant  ");
	setColor();
	printf("   vs");
	setColor(RED, BLACK);
	printf("     zombie! ! !");

	setColor();
	printf("     按下enter键即可开始游戏。ESC退出游戏");
}

void showMap()
{
	setCursorPos(0, TOP_HIGH);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			printf("#");
			for (int k = 0; k < COL_WIDTH; k++)
				printf("-");
		}
		printf("#\n");
		int x = 0, y = i * (ROW_HIGH + 1) + TOP_HIGH + 1;
		for (int j = 0; j < ROW_HIGH; j++)
		{
			for (int k = 0; k <= COL; k++)
			{
				setCursorPos(x, y);
				printf("|");
				x += COL_WIDTH + 1;
			}
			printf(" ");
			y++;
			x = 0;
		}
	}
	for (int j = 0; j < COL; j++)
	{
		printf("#");
		for (int k = 0; k < COL_WIDTH; k++)
			printf("-");
	}
	printf("#");
}

void showInfo()
{
	setCursorPos(2, 1);
	printf("阳光：%05d", sunlight);
	cout << endl;
	printf("提示：ESC退出游戏");
}

void showMessage(const char* message)
{
	setCursorPos(0, MESSAGE_LINE);
	for (int i = 0; i < WINDOWS_WIDTH ; i++)
		printf(" ");
	int left = (WINDOWS_WIDTH - strlen(message)) / 2;
	setCursorPos(left, MESSAGE_LINE);
	setColor(RED);
	printf("%s", message);
	setColor();
}

void showPlant(const Plant& plant)
{
	int plant_left = plant.get_x() * (COL_WIDTH + 1);
	int plant_top = plant.get_y() * (ROW_HIGH + 1) + TOP_HIGH;

	string name = plant.getID();
	int name_left = (COL_WIDTH - name.length()) / 2 + 1;
	setCursorPos(plant_left + name_left, plant_top + ROW_HIGH - 2);
	setColor(WHITE, plant.color);
	cout << name;
	setCursorPos(plant_left + 3, plant_top + 2);
	int hp_color= WHITE;
	setColor(BLACK, hp_color);
	cout << "hp:";
	setColor(BLACK, hp_color);
	printf("%3d", plant.current_hp);
	//printf("%d", plant.current_hp);
	setColor();
}

void cleanPlant(const Plant& plant)
{
	int plant_left = plant.x * (COL_WIDTH + 1);
	int plant_top = plant.y * (ROW_HIGH + 1) + TOP_HIGH;

	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(plant_left + 1, plant_top + i + 1);
		for (int j = 0; j < COL_WIDTH; j++)
			printf(" ");
	}
}

void showBullet(const Bullet& blt)
{

	setCursorPos(blt.get_x() - 1, blt.get_y());
	if (blt.get_x() % (COL_WIDTH + 1) == 1)//先清空并补全子弹上一个位置残留的影响
	{
		printf("|");
	}
	else
	{
		printf(" ");
	}
	setCursorPos(blt.get_x(), blt.get_y());
	setColor(blt.color);
	printf("●");
	setColor();
}

void cleanBullet(const Bullet& blt)
{
	setCursorPos(blt.get_x() - 1, blt.get_y());
	if (blt.get_x() % (COL_WIDTH + 1) == 0)
	{
		printf(" |");
	}
	else if (blt.get_x() % (COL_WIDTH + 1) == 1)
	{
		printf("| ");
	}
	else
	{
		printf("  ");
	}
	
}

void showZombie(const Zombie&zombie)
{
	int zombie_left = zombie.x;
	int zombie_top = zombie.y;

	string a=zombie.ZOMBIE_ID;
	int len = a.length();
	int name_left = (10 - len) / 2 + 1;

	setCursorPos(zombie_left + COL_WIDTH - 2, zombie_top + 2);
	if ((zombie_left + COL_WIDTH-2) % (COL_WIDTH + 1) == 0)//僵尸原来的边界位置 如果与列相交，输出|补充边界
	{
			printf("|");
	}
	else
	{
			printf(" ");
	}
	setCursorPos(zombie_left + name_left+1 + len, zombie_top + ROW_HIGH - 2);
	if ((zombie_left + name_left +1+ len) % (COL_WIDTH + 1) == 0)
	{
			printf("|");
	}
	else
	{
			printf(" ");
	}

	setCursorPos(zombie_left + name_left+1, zombie_top + ROW_HIGH - 2);
	setColor(WHITE, RED);
	cout << a;
	setCursorPos(zombie_left + 4, zombie_top + 2);
	int hp_color = WHITE;
	setColor(BLACK, hp_color);
	cout << "hp:";
	setColor(BLACK, hp_color);
	printf("%03d", zombie.current_hp);
	setColor();
}

void cleanZombie(const Zombie& zombie)
{
	int map_left = zombie.get_x();
	int map_top = zombie.get_y();
	setCursorPos(map_left + 1, map_top + 2);
	for (int i = 0; i < 10; i++)
	{
		if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
			printf("|");
		else
			printf(" ");
			
	}
	setCursorPos(map_left + 1, map_top + 4);
	for (int i = 0; i < 10; i++)
	{
		if ((map_left + 1 + i) % (COL_WIDTH + 1) == 0)
			printf("|");
		else
			printf(" ");

	}

}

void showselector()
{

	int x = shop.ms.get_x();
	int y = shop.ms.get_y();
	Plant* ps = plantlist.getPlant(x, y);
	setColor(GREEN);
	int block_left = x * (COL_WIDTH + 1);
	int block_top = y * (ROW_HIGH + 1) + TOP_HIGH;
	setCursorPos(block_left, block_top);
	printf("#");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("#");
	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(block_left, block_top + i + 1);
		printf("|");
		setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
		printf("|");
	}
	setCursorPos(block_left, block_top + ROW_HIGH + 1);
	printf("#");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("#");


}
void showShop()
{
	for (int i = 0; i < PLANT_KIND_NUM; i++)
	{
		const char* name = plantname_list[i];
		int color = shop.ps.getPlant() == i ? (shop.status == 0 ? YELLOW : RED) : WHITE;
		setCursorPos((i % 4) * (WINDOWS_WIDTH - 3) / 4 + 1, WINDOWS_HIGH - BOTTOM_HIGH + (i / 4) * 2);
		setColor(BLACK, color);
		printf("%c. %s $%03d", (char)(i >= 9 ? ('A' + i - 9) : '0' + i + 1), name, cost[i]);
	
	}
	if (shop.status == 1)
	{
		showselector();
		
	}
	setCursorPos(1, WINDOWS_HIGH - 2);
	setColor(WHITE, GREY);
	cout << std::left;
	cout << std::right;
	setColor();
	return;
}

void cleanselector()
{
	setColor();
	int x = shop.ms.get_x();
	int y= shop.ms.get_y();
	int block_left = x * (COL_WIDTH + 1);
	int block_top = y * (ROW_HIGH + 1) + TOP_HIGH;
	setCursorPos(block_left, block_top);
	printf("#");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("#");
	for (int i = 0; i < ROW_HIGH; i++)
	{
		setCursorPos(block_left, block_top + i + 1);
		printf("|");
		setCursorPos(block_left + COL_WIDTH + 1, block_top + i + 1);
		printf("|");
	}
	setCursorPos(block_left, block_top + ROW_HIGH + 1);
	printf("#");
	for (int i = 0; i < COL_WIDTH; i++)
		printf("-");
	printf("#");
}

