#include <windows.h>
#include <conio.h>
#include <time.h>
#include "globalv.h"
#include "config.h"
int level = 7; 
int sunlight = 500; // 初始阳光数
int alive = 1; 
Shop shop;
const char* plantname_list[];
void Game();
PlantList plantlist;
BulletList bulletlist;
ZombieList zombielist;
int main()
{
	initWindow();
	int play_game = 1;
	showImg();
	while (play_game)
	{
		int ch = _getch();
		switch (ch)
		{
		case ENTER:
			Game();
			break;
		case ESC:
			exit(-1);
		default:
			break;
		}
	}
	return 0;
}

void Game()
{
	system("cls");//清屏功能
	int regame = 0;
	ULONGLONG last_time = GetTickCount64();
	showMap();
	showMessage("欢迎来到植物大战僵尸");
	while (alive)
	{
		while (GetTickCount64() - last_time < SLEEP_TIME);//设置时钟时间
		last_time = GetTickCount64();
		if (_kbhit())
		{
			int key = _getch();
			if (key == ESC)
			{
				showMessage("Game Over! 游戏结束！");
				exit(-1);
			}
			shop.mapdoing(key);
		}
		zombielist.zombiedoing();//对僵尸类操作，并输出
		plantlist.plantsdoing();//对植物类操作
		bulletlist.bulletdoing();//对子弹类操作
		showInfo();//提示阳光数
		shop.wait();//冷却时间
		showShop();//输出商店
	}
	if (!alive)
		showMessage("Game Over! 游戏结束！");
}
