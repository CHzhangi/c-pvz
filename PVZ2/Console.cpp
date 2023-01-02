#include "globalv.h"
#include <windows.h>
#include <time.h>
static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void initWindow()
{
	SetConsoleTitleA("PVZ 191220172"); //修改窗口名字
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	GetWindowRect(hWnd, &rc);
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
	char cmd[] = "mode con cols=0000 lines=0000";
	char buffer_w[64];
	char buffer_h[64];
	int ret = snprintf(buffer_w, sizeof buffer_w, "%04d", WINDOWS_WIDTH);
	if (ret < 0)
		exit(-1);
	ret = snprintf(buffer_h, sizeof buffer_h, "%04d", WINDOWS_HIGH);
	if (ret < 0)
		exit(-1);
	cmd[14] = buffer_w[0]; cmd[15] = buffer_w[1]; cmd[16] = buffer_w[2]; cmd[17] = buffer_w[3];
	cmd[25] = buffer_h[0]; cmd[26] = buffer_h[1]; cmd[27] = buffer_h[2]; cmd[28] = buffer_h[3];
	system(cmd);
	setCursorHide(0);
	setColor();
	srand((unsigned)time(0));
}

void setCursorHide(bool visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = visible; //隐藏或显示控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	return;
}

void setCursorPos(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}

void setColor(int font_color, int background_color)
{
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (font_color == WHITE &&
		background_color == YELLOW || background_color == WHITE || background_color == BLUE || background_color == CYAN || background_color == DARK_WHITE || background_color == font_color)
		font_color = BLACK;
	SetConsoleTextAttribute(handle, background_color << 4 | font_color);
}