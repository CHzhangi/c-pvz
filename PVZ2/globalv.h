#ifndef __HEAD_FILE__
#define __HEAD_FILE__
#include "config.h" //�궨��������Ϣ
#include "Console.h" // ����̨״̬
#include "Display.h" // UIģ��
#include "Plant.h" //ֲ��ģ��
#include "Bullet.h" //�ӵ�ģ��
#include "Zombie.h" //��ʬģ��
#include "map.h" //�̵�ģ��
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <random>
extern int sunlight; // ������
extern int alive; // ��Ϸ�Ƿ���
extern PlantList plantlist; // ���е�ֲ��
extern BulletList bulletlist; // ���е��ӵ�
extern ZombieList zombielist; // ���еĽ�ʬ
extern Shop shop; //�̵�
extern const char* plantname_list[]; // ֲ������
extern int cost[];
#endif