#pragma once

extern int _WAIT[]; // �̵���ȴ

class PlantSelector
{
private:
	int pid;
public:
	PlantSelector();
	~PlantSelector();
	void reinit();
	void setPlant(int pid);
	int getPlant() const;
};

class MapSelector
{
	int x, y;
public:
	MapSelector();
	~MapSelector();
	void reinit();
	void move(int direction);
	int get_x() const;
	int get_y() const;
};

class Shop
{
private:
	PlantSelector ps;
	MapSelector ms;
	int status; // 0 ѡ��ֲ��  1 ѡ���ͼλ�� 
	int* wait_time;
	int buyPlant();
public:
	Shop();
	void choosePlant();
	void unchoosePlant();
	void mapdoing(int key);
	void wait();// ��ȴ
	friend void showShop();
	friend void cleanselector();
	friend void showselector();
};

#pragma once
