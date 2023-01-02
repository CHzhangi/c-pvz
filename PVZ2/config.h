#define COL 12 //行
#define ROW 5 //列
#define ROW_HIGH 6 //行高
#define COL_WIDTH 12 //列宽
#define MESSAGE_LINE 3 //消息在第几行显示
#define PLANT_KIND_NUM 2
#define SLEEP_TIME 20 //每次循环等待时间，ms
#define COLOR_TIME 15 //颜色闪烁时间
#define NEW_ZOMBIE_X (WINDOWS_WIDTH - COL_WIDTH) //新僵尸的横坐标
#define FIRST_ZOMBIE_TIME 0 //首次出现僵尸的时间
#define TOP_HIGH 4 //顶部栏高度
#define BOTTOM_HIGH (2 + 2 * ((PLANT_KIND_NUM + 3) / 4)) //底部栏高度
#define WINDOWS_HIGH (ROW * (ROW_HIGH + 1) + TOP_HIGH + BOTTOM_HIGH + 1) //窗口高度
#define WINDOWS_WIDTH (COL * (COL_WIDTH + 1) + 2) //窗口宽度
#define BLACK 0x0
#define DARK_BLUE 0x1
#define DARK_GREEN 0x2
#define DARK_CYAN 0x3
#define DARK_RED 0x4
#define DARK_PURPLE 0x5
#define DARK_YELLOW 0x6
#define DARK_WHITE 0x7
#define GREY 0x8
#define BLUE 0x9
#define GREEN 0xa
#define CYAN 0xb
#define RED 0xc
#define PURPLE 0xd
#define YELLOW 0xe
#define WHITE 0xf

// 按键
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define ESC 27
#define NUM0 48
#define NUM1 (NUM0+1)
#define NUM2 (NUM0+2)


