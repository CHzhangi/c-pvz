#pragma once
#pragma once
#include "Plant.h"
#include "Bullet.h"
#include "Zombie.h"

void showImg();//��ʼ��ҳ����Ϣ

void showMap();//��ʾ��ͼ

void showMessage(const char* message);
void showPlant(const Plant& plant);
void cleanPlant(const Plant& plant);
void showBullet(const Bullet& blt);
void cleanBullet(const Bullet& blt);
void showZombie(const Zombie& zombie);
void cleanZombie(const Zombie& zombie);
void showShop();
void showInfo();
void showselector();
void cleanselector();
