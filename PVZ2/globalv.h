#ifndef __HEAD_FILE__
#define __HEAD_FILE__
#include "config.h" //宏定义配置信息
#include "Console.h" // 控制台状态
#include "Display.h" // UI模块
#include "Plant.h" //植物模块
#include "Bullet.h" //子弹模块
#include "Zombie.h" //僵尸模块
#include "map.h" //商店模块
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <random>
extern int sunlight; // 阳光数
extern int alive; // 游戏是否存活
extern PlantList plantlist; // 所有的植物
extern BulletList bulletlist; // 所有的子弹
extern ZombieList zombielist; // 所有的僵尸
extern Shop shop; //商店
extern const char* plantname_list[]; // 植物名字
extern int cost[];
#endif