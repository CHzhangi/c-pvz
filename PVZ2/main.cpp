#include <windows.h>
#include <conio.h>
#include <time.h>
#include "globalv.h"
#include "config.h"
int level = 7; 
int sunlight = 500; // ��ʼ������
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
	system("cls");//��������
	int regame = 0;
	ULONGLONG last_time = GetTickCount64();
	showMap();
	showMessage("��ӭ����ֲ���ս��ʬ");
	while (alive)
	{
		while (GetTickCount64() - last_time < SLEEP_TIME);//����ʱ��ʱ��
		last_time = GetTickCount64();
		if (_kbhit())
		{
			int key = _getch();
			if (key == ESC)
			{
				showMessage("Game Over! ��Ϸ������");
				exit(-1);
			}
			shop.mapdoing(key);
		}
		zombielist.zombiedoing();//�Խ�ʬ������������
		plantlist.plantsdoing();//��ֲ�������
		bulletlist.bulletdoing();//���ӵ������
		showInfo();//��ʾ������
		shop.wait();//��ȴʱ��
		showShop();//����̵�
	}
	if (!alive)
		showMessage("Game Over! ��Ϸ������");
}
