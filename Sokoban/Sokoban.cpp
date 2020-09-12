#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <io.h>
#include <conio.h>
using namespace std;
void gotoxy(HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}
void setcolor(HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}
void showch(HANDLE hout, const int X, const int Y, const int bg_color, const int fg_color, const char ch, const int n)
{
	int i;
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);
	for (i = 0; i < n; i++)
		putchar(ch);
}
void showch1(HANDLE hout, const int X, const int Y, const int bg_color, const int fg_color, const char ch[])
{
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);
	cout << ch << endl;

}
void findFile(char a[][30], int y)//读取文件
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int i;
	int j = 3;
	char c[100];
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	strcpy(c, ".\\关卡\\");
	strcat(c, file.name);
	ifstream infile;
	infile.open(c, ios::in);
	if (infile.is_open() == 0)
	{
		gotoxy(hout, 0, 0);
		showch1(hout, 0, 0, 0, 7, "                      ");
		cout << "打开文件失败" << endl;
		return;
	}
	for (i = 1; i <= 16; i++)
		infile >> a[i];
	infile.close();
}
void print_guanqia()//打印初始化的关卡
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int j;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	gotoxy(hout, 98, 2);
	cout << "请选择关卡";
	showch1(hout, 97, 3, 0, 7, "╔════════╗");
	for (j = 4; j <= 31; j++)
		showch1(hout, 97, j, 0, 7, "║        ║");
	showch1(hout, 97, 32, 0, 7, "╚════════╝");
	j = 4;
	while (k != -1)
	{
		if (j == 32)
			break;
		if (j == 4)
			showch1(hout, 99, j, 7, 0, "       ");
		else
			showch1(hout, 99, j, 0, 7, "       ");
		if (file.name[17] == '.')
		{
			gotoxy(hout, 99, j);
			cout << "关卡" << file.name[14] << file.name[15] << file.name[16];
			j++;
		}
		k = _findnext(handle, &file);
	}
}
void solve_guanqia(int y, int *y1)//在指定位置显示对应关卡
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	gotoxy(hout, 99, *y1);
	cout << "关卡" << file.name[14] << file.name[15] << file.name[16];
}
void reprint_guanqia_down(int y, int y1)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	int y3, y4;
	long handle;
	int k;
	int j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	for (y1 = 29, y3 = y; y1 >= 4; y1--)
		y3--;
	y1 = 4;
	y4 = 4;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
		{
			if (y1 == 32)
				break;
			if (y4 >= y3)
			{
				showch1(hout, 99, y1, 0, 7, "       ");
				gotoxy(hout, 99, y1);
				cout << "关卡" << file.name[14] << file.name[15] << file.name[16];
				y1++;
			}
			y4++;
		}
		k = _findnext(handle, &file);
	}
}
void reprint_guanqia_up(int y, int y1)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	int y3, y4;
	long handle;
	int k;
	int j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	y3 = y - 1;
	y1 = 4;
	y4 = 4;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
		{
			if (y1 == 32)
				break;
			if (y4 >= y3)
			{
				showch1(hout, 99, y1, 0, 7, "       ");
				gotoxy(hout, 99, y1);
				cout << "关卡" << file.name[14] << file.name[15] << file.name[16];
				y1++;
			}
			y4++;
		}
		k = _findnext(handle, &file);
	}
}
int check()//检查是否到最后一个
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int t = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-*.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			t++;
		if (file.name[14] == 'e'&&file.name[15] == 'r'&&file.name[16] == 'r')
			break;
		k = _findnext(handle, &file);
	}
	return t;
}
void print_choice(int *s)//方向键控制并选择对应关卡
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int y = 4;
	int y1 = 4;
	char key;
	print_guanqia();//打印关卡
	gotoxy(hout, 99, y1);
	while (1)
	{
		key = _getch();
		if (key == 13)
		{
			*s = y;
			break;
		}
		if (key = -32)
		{
			key = _getch();
			if (y1 > 4 && y1 < 31)
			{
				if (key == 72)
				{
					showch1(hout, 99, y1, 0, 7, "       ");
					solve_guanqia(y, &y1);
					y = y - 1;
					y1 = y1 - 1;
					showch1(hout, 99, y1, 7, 0, "       ");
					solve_guanqia(y, &y1);
					gotoxy(hout, 99, y1);
					key = 0;
				}
				if (key == 80)
				{
					showch1(hout, 99, y1, 0, 7, "       ");
					solve_guanqia(y, &y1);
					y = y + 1;
					y1 = y1 + 1;
					showch1(hout, 99, y1, 7, 0, "       ");
					solve_guanqia(y, &y1);
					gotoxy(hout, 99, y1);
					key = 0;
				}
			}
			if (y1 == 31)
			{
				if (y < check())
				{
					if (key == 72)
					{
						showch1(hout, 99, y1, 0, 7, "       ");
						solve_guanqia(y, &y1);
						y = y - 1;
						y1 = y1 - 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
					if (key == 80)
					{
						reprint_guanqia_down(y, y1);
						y = y + 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
				}
				else
				{
					if (key == 72)
					{
						showch1(hout, 99, y1, 0, 7, "       ");
						solve_guanqia(y, &y1);
						y = y - 1;
						y1 = y1 - 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
				}
			}
			if (y1 == 4)
			{
				if (y == 4)
				{
					if (key == 80)
					{
						showch1(hout, 99, y1, 0, 7, "       ");
						solve_guanqia(y, &y1);
						y = y + 1;
						y1 = y1 + 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
				}
				else
				{
					if (key == 72)
					{
						reprint_guanqia_up(y, y1);
						y = y - 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
					if (key == 80)
					{
						showch1(hout, 99, y1, 0, 7, "       ");
						solve_guanqia(y, &y1);
						y = y + 1;
						y1 = y1 + 1;
						showch1(hout, 99, y1, 7, 0, "       ");
						solve_guanqia(y, &y1);
						gotoxy(hout, 99, y1);
						key = 0;
					}
				}
			}
		}
	}
}
void print_picture(int i, int j, char a[][30])//每个方块
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int k, l;
	if (a[i][j] == '9')
	{
		k = 0;
		l = 0;
	}
	else if (a[i][j] == '0')
	{
		k = 7;
		l = 7;
	}
	else if (a[i][j] == 'W' || a[i][j] == 'w')
	{
		k = 4;
		l = 0;
	}
	else if (a[i][j] == 'B' || a[i][j] == 'b')
	{
		k = 2;
		l = 14;
	}
	else if (a[i][j] == 'F' || a[i][j] == 'f')
	{
		k = 11;
		l = 10;
	}
	else if (a[i][j] == 'S' || a[i][j] == 's')
	{
		k = 9;
		l = 14;
	}
	else if (a[i][j] == 'R' || a[i][j] == 'r')
	{
		k = 14;
		l = 12;
	}
	showch(hout, 6 * j + 1, 3 * i - 1, k, l, ' ', 6);
	showch(hout, 6 * j + 1, 3 * i, k, l, ' ', 6);
	showch(hout, 6 * j + 1, 3 * i + 1, k, l, ' ', 6);
	showch1(hout, 6 * j + 1, 3 * i - 1, k, l, "╔═══╗");
	showch1(hout, 6 * j + 1, 3 * i, k, l, "║   ║");
	showch1(hout, 6 * j + 1, 3 * i + 1, k, l, "╚═══╝");
	gotoxy(hout, 6 * j + 3, 3 * i);
	if (a[i][j] == 'W' || a[i][j] == 'w')
		cout << "XX";
	else if (a[i][j] == 'B' || a[i][j] == 'R' || a[i][j] == 'b' || a[i][j] == 'r')
		cout << "★";
	else if (a[i][j] == 'F' || a[i][j] == 'f')
		cout << "●";
	else if (a[i][j] == 'S' || a[i][j] == 's')
		cout << "♀";
}
void find_hang_lie(int *s, int *t, char a[][30])//行，列数
{
	int i;
	for (i = 1, *s = 0;; i++, (*s)++)
	{
		if (a[i][0] == '\0')
			break;
		if (*s == 16)
			break;
	}
	*t = strlen(a[1]) - 1;
	if (*t > 15)
		*t = 15;
}
void copy_(int *s, int *t, char a[][30], char c[][30])//初始化图案保留
{
	int i, j;
	for (i = 1; i <= *s; i++)
	{
		for (j = 0; j <= *t; j++)
			c[i][j] = a[i][j];
	}
}
void print_all(int *s, int *t, char a[][30])//打印界面
{
	int i, j;
	for (i = 1; i <= *s; i++)
	{
		for (j = 0; j <= *t; j++)
			print_picture(i, j, a);
	}
	cout << endl;
	cout << endl;
}
void print_introduction(int *y)
{
	if (*y != check())
	{
		cout << endl;
		cout << "上下左右箭头键：移动" << endl;
		cout << "R（r）：本关重新开始" << endl;
		cout << "Backspace：回退一步" << endl;
		cout << "Q（q）：退出游戏并返回主菜单" << endl;
		cout << "S（s）：将执行到按S（s）键的所有步骤写入答案文件中" << endl;
	}
	else
	{
		cout << endl;
		cout << "该关卡为错误关卡！" << endl;
	}
}
void find_s(int *x1, int *y1, int *s, int *t, char a[][30])//寻找初始启动位置
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	for (i = 1; i <= *s; i++)
	{
		for (j = 0; j <= *t; j++)
		{
			if (a[i][j] == 'S' || a[i][j] == 's')
			{
				*x1 = i;
				*y1 = j;
				gotoxy(hout, 6 * (*y1) + 3, 3 * (*x1));
			}
		}
	}
}
void mark_f(int *s, int *t, char a[][30], int b[][30])//记录特殊点的坐标
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	for (i = 1; i <= *s; i++)
	{
		for (j = 0; j <= *t; j++)
		{
			if (a[i][j] == 'F' || a[i][j] == 'f')
				b[i][j] = 1;
			if (a[i][j] == 'R' || a[i][j] == 'r')
				b[i][j] = 2;
		}
	}
}
void move_(char *key, char a[][30], int *x1, int *y1, int b[][30], int *count, char direction[], int *i)//移动
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (b[*x1][*y1] == 1 || b[*x1][*y1] == 2)
		a[*x1][*y1] = 'F';
	if (b[*x1][*y1] == 0)
		a[*x1][*y1] = '0';
	if (*key == 75)//左
	{
		if (a[*x1][*y1 - 1] == '0' || a[*x1][*y1 - 1] == 'F' || a[*x1][*y1 - 1] == 'f'
			|| ((a[*x1][*y1 - 1] == 'B' || a[*x1][*y1 - 1] == 'b' || a[*x1][*y1 - 1] == 'R' || a[*x1][*y1 - 1] == 'r')
				&& (a[*x1][*y1 - 2] == '0' || a[*x1][*y1 - 2] == 'F' || a[*x1][*y1 - 2] == 'f')))
		{
			if (a[*x1][*y1 - 1] == '0' || a[*x1][*y1 - 1] == 'F' || a[*x1][*y1 - 1] == 'f')
				print_picture(*x1, *y1, a);
			if (a[*x1][*y1 - 1] == 'B' || a[*x1][*y1 - 1] == 'b' || a[*x1][*y1 - 1] == 'R' || a[*x1][*y1 - 1] == 'r')
			{
				if (a[*x1][*y1 - 2] == '0')
				{
					a[*x1][*y1 - 2] = 'B';
					print_picture(*x1, *y1 - 2, a);
					print_picture(*x1, *y1, a);
				}
				if (a[*x1][*y1 - 2] == 'F' || a[*x1][*y1 - 2] == 'f')
				{
					a[*x1][*y1 - 2] = 'R';
					print_picture(*x1, *y1 - 2, a);
					print_picture(*x1, *y1, a);
				}
			}
			*y1 = *y1 - 1;
			(*count)++;
			direction[(*i)++] = 'L';
		}
	}
	if (*key == 77)//右
	{
		if (a[*x1][*y1 + 1] == '0' || a[*x1][*y1 + 1] == 'F' || a[*x1][*y1 + 1] == 'f'
			|| ((a[*x1][*y1 + 1] == 'B' || a[*x1][*y1 + 1] == 'b' || a[*x1][*y1 + 1] == 'R' || a[*x1][*y1 + 1] == 'r')
				&& (a[*x1][*y1 + 2] == '0' || a[*x1][*y1 + 2] == 'F' || a[*x1][*y1 + 2] == 'f')))
		{
			if (a[*x1][*y1 + 1] == '0' || a[*x1][*y1 + 1] == 'F' || a[*x1][*y1 + 1] == 'f')
				print_picture(*x1, *y1, a);
			if (a[*x1][*y1 + 1] == 'B' || a[*x1][*y1 + 1] == 'b' || a[*x1][*y1 + 1] == 'R' || a[*x1][*y1 + 1] == 'r')
			{
				if (a[*x1][*y1 + 2] == '0')
				{
					a[*x1][*y1 + 2] = 'B';
					print_picture(*x1, *y1 + 2, a);
					print_picture(*x1, *y1, a);
				}
				if (a[*x1][*y1 + 2] == 'F' || a[*x1][*y1 + 2] == 'f')
				{
					a[*x1][*y1 + 2] = 'R';
					print_picture(*x1, *y1 + 2, a);
					print_picture(*x1, *y1, a);
				}
			}
			*y1 = *y1 + 1;
			(*count)++;
			direction[(*i)++] = 'R';
		}
	}
	if (*key == 72)//上
	{
		if (a[*x1 - 1][*y1] == '0' || a[*x1 - 1][*y1] == 'F' || a[*x1 - 1][*y1] == 'f'
			|| ((a[*x1 - 1][*y1] == 'B' || a[*x1 - 1][*y1] == 'b' || a[*x1 - 1][*y1] == 'R' || a[*x1 - 1][*y1] == 'r')
				&& (a[*x1 - 2][*y1] == '0' || a[*x1 - 2][*y1] == 'F' || a[*x1 - 2][*y1] == 'f')))
		{
			if (a[*x1 - 1][*y1] == '0' || a[*x1 - 1][*y1] == 'F' || a[*x1 - 1][*y1] == 'f')
				print_picture(*x1, *y1, a);
			if (a[*x1 - 1][*y1] == 'B' || a[*x1 - 1][*y1] == 'b' || a[*x1 - 1][*y1] == 'R' || a[*x1 - 1][*y1] == 'r')
			{
				if (a[*x1 - 2][*y1] == '0')
				{
					a[*x1 - 2][*y1] = 'B';
					print_picture(*x1 - 2, *y1, a);
					print_picture(*x1, *y1, a);
				}
				if (a[*x1 - 2][*y1] == 'F' || a[*x1 - 2][*y1] == 'f')
				{
					a[*x1 - 2][*y1] = 'R';
					print_picture(*x1 - 2, *y1, a);
					print_picture(*x1, *y1, a);
				}
			}
			*x1 = *x1 - 1;
			(*count)++;
			direction[(*i)++] = 'U';
		}
	}
	if (*key == 80)//下
	{
		if (a[*x1 + 1][*y1] == '0' || a[*x1 + 1][*y1] == 'F' || a[*x1 + 1][*y1] == 'f'
			|| ((a[*x1 + 1][*y1] == 'B' || a[*x1 + 1][*y1] == 'b' || a[*x1 + 1][*y1] == 'R' || a[*x1 + 1][*y1] == 'r')
				&& (a[*x1 + 2][*y1] == '0' || a[*x1 + 2][*y1] == 'F' || a[*x1 + 2][*y1] == 'f')))
		{
			if (a[*x1 + 1][*y1] == '0' || a[*x1 + 1][*y1] == 'F' || a[*x1 + 1][*y1] == 'f')
				print_picture(*x1, *y1, a);
			if (a[*x1 + 1][*y1] == 'B' || a[*x1 + 1][*y1] == 'b' || a[*x1 + 1][*y1] == 'R' || a[*x1 + 1][*y1] == 'r')
			{
				if (a[*x1 + 2][*y1] == '0')
				{
					a[*x1 + 2][*y1] = 'B';
					print_picture(*x1 + 2, *y1, a);
					print_picture(*x1, *y1, a);
				}
				if (a[*x1 + 2][*y1] == 'F' || a[*x1 + 2][*y1] == 'f')
				{
					a[*x1 + 2][*y1] = 'R';
					print_picture(*x1 + 2, *y1, a);
					print_picture(*x1, *y1, a);
				}
			}
			*x1 = *x1 + 1;
			(*count)++;
			direction[(*i)++] = 'D';
		}
	}
	*key = 0;
	a[*x1][*y1] = 'S';
	print_picture(*x1, *y1, a);
	gotoxy(hout, 6 * (*y1) + 3, 3 * (*x1));
}
bool check_success(int *s, int *t, char a[][30])//判断游戏是否成功
{
	int i, j, count = 0;
	for (i = 1; i <= *s; i++)
	{
		for (j = 0; j <= *t; j++)
		{
			if (a[i][j] == 'B' || a[i][j] == 'b')
				count++;
		}
	}
	if (count == 0)
		return 1;
	else
		return 0;
}
void update_b(int b[][30])//b清零
{
	int i, j;
	for (i = 0; i <= 16; i++)
	{
		for (j = 0; j <= 29; j++)
			b[i][j] = 0;
	}
}
void find_answer(char a[][30], int b[][30], int *x1, int *y1, int y, char *key, int *count, int *s, int *t, char direction[], int *i)//读取答案文件并演示
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int num;
	int j = 3;
	int no = 0;
	int n = 0;
	char ch;
	char c[100];
	char d[3];
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	d[0] = file.name[14];
	d[1] = file.name[15];
	d[2] = file.name[16];
	j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***-ans.txt", &file);
	while (k != -1)
	{
		if (file.name[21] == '.')
		{
			if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2])
				break;
		}
		k = _findnext(handle, &file);
	}
	if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2])
	{
		strcpy(c, ".\\关卡\\");
		strcat(c, file.name);
		ifstream infile;
		infile.open(c, ios::in);
		if (infile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		while (infile >> ch)
		{
			n++;
			if (ch != 'L'&&ch != 'l'&&ch != 'R'&&ch != 'r'&&ch != 'U'&&ch != 'u'&&ch != 'D'&&ch != 'd')
			{
				no++;
				break;
			}
		}
		infile.close();
		if (no == 0)
		{
			infile.open(c, ios::in);
			if (infile.is_open() == 0)
			{
				showch1(hout, 0, 0, 0, 7, "                      ");
				gotoxy(hout, 0, 0);
				cout << "打开文件失败" << endl;
				return;
			}
			while (infile >> ch)
			{
				if (ch == 'L' || ch == 'l')
					*key = 75;
				if (ch == 'R' || ch == 'r')
					*key = 77;
				if (ch == 'U' || ch == 'u')
					*key = 72;
				if (ch == 'D' || ch == 'd')
					*key = 80;
				num = *count;
				move_(key, a, x1, y1, b, count, direction, i);
				if (*count == num && check_success(s, t, a) == 0)
				{
					showch1(hout, 0, 0, 0, 7, "                      ");
					gotoxy(hout, 0, 0);
					cout << "演示文件第" << (*count + 1) << "个步骤出错！";
					break;
				}
				else
				{
					gotoxy(hout, 98, 33);
					setcolor(hout, 0, 7);
					cout << "步数：" << *count;
				}
			}
			infile.close();
		}
		else
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "第" << n << "个步骤存在非法字符！";
			*key = 0;
		}
	}
	else
	{
		showch1(hout, 0, 0, 0, 7, "                      ");
		gotoxy(hout, 0, 0);
		cout << "演示文件不存在！";
		*key = 0;
	}
}
void update_direction(char direction[])
{
	int i;
	for (i = 0; i <= 19999; i++)
		direction[i] = '\0';
}
void mark_score(int y, int *count)//成功后记录步数
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int t;
	int j = 3;
	char c[100];
	char d[4];
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	d[0] = file.name[14];
	d[1] = file.name[15];
	d[2] = file.name[16];
	d[3] = '\0';
	j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***-score.txt", &file);
	while (k != -1)
	{
		if (file.name[23] == '.')
		{
			if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2])
				break;
		}
		k = _findnext(handle, &file);
	}
	strcpy(c, ".\\关卡\\");
	strcat(c, "Sokoban-Level-");
	strcat(c, d);
	strcat(c, "-score.txt");
	if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2] && file.name[23] == '.')
	{
		ifstream infile(c, ios::in);
		if (infile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		infile >> t;
		ofstream outfile(c, ios::in);
		if (outfile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		if (*count >= t)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 1);
			cout << "第" << d << "关的最好成绩是" << t << "步，本次用了" << *count << "步";
		}
		else
		{
			outfile << *count;
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 1);
			cout << "新纪录诞生，步数已成功放入得分文件中！";
		}
		outfile.close();
		infile.close();
	}
	else
	{
		ofstream outfile(c, ios::out);
		if (outfile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		outfile << *count;
		showch1(hout, 0, 0, 0, 7, "                      ");
		gotoxy(hout, 0, 1);
		cout << "步数已成功放入得分文件中！";
		outfile.close();
	}
}
void mark_direction(char direction[], int y)//记录方向
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	_finddata_t file;
	long handle;
	int k;
	int i;
	int j = 3;
	char c[100];
	char d[4];
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***.txt", &file);
	while (k != -1)
	{
		if (file.name[17] == '.')
			j++;
		if (j == y)
			break;
		k = _findnext(handle, &file);
	}
	d[0] = file.name[14];
	d[1] = file.name[15];
	d[2] = file.name[16];
	d[3] = '\0';
	j = 3;
	k = handle = _findfirst(".\\关卡\\Sokoban-Level-***-ans.txt", &file);
	while (k != -1)
	{
		if (file.name[21] == '.')
		{
			if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2])
				break;
		}
		k = _findnext(handle, &file);
	}
	strcpy(c, ".\\关卡\\");
	strcat(c, "Sokoban-Level-");
	strcat(c, d);
	strcat(c, "-ans.txt");
	if (file.name[14] == d[0] && file.name[15] == d[1] && file.name[16] == d[2] && file.name[21] == '.')
	{
		ofstream outfile(c, ios::out);
		if (outfile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		for (i = 1;; i++)
		{
			if (direction[i] == '\0')
				break;
			outfile << direction[i];
		}
		showch1(hout, 0, 0, 0, 7, "                      ");
		gotoxy(hout, 0, 0);
		cout << "所有步骤已写入答案文件中！";
		outfile.close();
	}
	else
	{
		ofstream outfile(c, ios::out);
		if (outfile.is_open() == 0)
		{
			showch1(hout, 0, 0, 0, 7, "                      ");
			gotoxy(hout, 0, 0);
			cout << "打开文件失败" << endl;
			return;
		}
		for (i = 1;; i++)
		{
			if (direction[i] == '\0')
				break;
			outfile << direction[i];
		}
		showch1(hout, 0, 0, 0, 7, "                      ");
		gotoxy(hout, 0, 0);
		cout << "所有步骤已写入答案文件中！";
		outfile.close();
	}
}
void mark_bk(char a[][30], char bk[][17][30], int *s, int *t, int *count)//回退
{
	int j, k;
	for (j = 1; j <= *s; j++)
	{
		for (k = 0; k <= *t; k++)
			bk[*count][j][k] = a[j][k];
	}
}
void update_bk(char bk[][17][30])//bk清零
{
	int i, j, k;
	for (i = 0; i <= 19999; i++)
	{
		for (j = 0; j <= 16; j++)
		{
			for (k = 0; k <= 29; k++)
				bk[i][j][k] = '\0';
		}
	}
}
void print_bk(char a[][30], char bk[][17][30], int *s, int *t, int *count)
{
	int j, k;
	for (j = 1; j <= *s; j++)
	{
		for (k = 0; k <= *t; k++)
			a[j][k] = bk[*count][j][k];
	}
	print_all(s, t, a);
}
char bk[20000][17][30];
int main()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	char key;
	char a[17][30], c[17][30];
	char direction[20000];//存储方向
	int b[17][30];//记录特殊点的坐标
	int y;//关卡对应量
	int s, t;//记录字符串中字符的行（s）列（t）数
	while (1)
	{
		cout << "-------------------------------------" << endl;
		cout << "子题目1（显示关卡与对应图形界面）" << endl;
		cout << "子题目2（“推箱子”游戏完整版）" << endl;
		cout << "子题目3（“推箱子”游戏解题步骤演示）" << endl;
		cout << "-------------------------------------" << endl;
		cout << "选择0-3（0为直接退出）：";
		key = _getch();
		if (key == '0')
			break;
		else if (key == '1')//子题目1
		{
			system("cls");
			system("mode con cols=110 lines=112");
			print_choice(&y);//选择对应关卡
			findFile(a, y);//扫描对应文件并打开
			find_hang_lie(&s, &t, a);//计算行列数
			print_all(&s, &t, a);//打印界面
			setcolor(hout, 0, 7);
			while (1)
			{
				cout << "按“q”键退出。" << endl;
				key = _getch();
				if (key == 'q')
					break;
			}
			system("cls");
			system("mode con cols=82 lines=25");
		}
		else if (key == '2')//子题目2
		{
			system("cls");
			system("mode con cols=110 lines=112");
			int count = 0;//步数
			print_choice(&y);//选择对应关卡
			findFile(a, y);//扫描对应文件并打开
			find_hang_lie(&s, &t, a);//计算行列数
			print_all(&s, &t, a);//打印界面
			copy_(&s, &t, a, c);//初始化图案保留
			setcolor(hout, 0, 7);
			print_introduction(&y);
			if (y != check())
			{
				gotoxy(hout, 98, 33);
				setcolor(hout, 0, 7);
				cout << "步数：" << count;
			}
			int x1, y1;
			int i = 1;//记录方向编号
			find_s(&x1, &y1, &s, &t, a);//寻找初始启动位置
			update_b(b);//b清零
			update_direction(direction);//direction清零
			update_bk(bk);//bk清零
			mark_f(&s, &t, a, b); //记录特殊点的坐标
			mark_bk(a, bk, &s, &t, &count);//回退记录
			while (y != check())
			{
				key = _getch();
				if (key == 'R' || key == 'r')
				{
					count = 0;
					i = 1;
					showch1(hout, 98, 33, 0, 7, "         ");
					gotoxy(hout, 98, 33);
					setcolor(hout, 0, 7);
					cout << "步数：" << count;
					copy_(&s, &t, c, a);
					print_all(&s, &t, a);//重新打印最初界面
					find_s(&x1, &y1, &s, &t, a);//寻找初始启动位置
					update_b(b);//b清零
					update_direction(direction);//direction清零
					update_bk(bk);//bk清零
					mark_f(&s, &t, a, b);//记录特殊点的坐标
					mark_bk(a, bk, &s, &t, &count);//回退记录
				}
				if (key == 8 && count != 0)
				{
					direction[count] = '\0';
					count--;
					print_bk(a, bk, &s, &t, &count);
					find_s(&x1, &y1, &s, &t, a);//寻找初始启动位置
					update_b(b);//b清零
					mark_f(&s, &t, a, b);//记录特殊点的坐标
					showch1(hout, 98, 33, 0, 7, "         ");
					gotoxy(hout, 98, 33);
					setcolor(hout, 0, 7);
					cout << "步数：" << count;
				}
				if (key == 'S' || key == 's')
					mark_direction(direction, y);//记录方向
				if (key == 'Q' || key == 'q')//直接返回主菜单
					break;
				if (key == -32)
				{
					key = _getch();
					move_(&key, a, &x1, &y1, b, &count, direction, &i);//移动
					mark_bk(a, bk, &s, &t, &count);//回退记录
					gotoxy(hout, 98, 33);
					setcolor(hout, 0, 7);
					cout << "步数：" << count;
					if (check_success(&s, &t, a) == 1)//判断游戏是否成功
					{
						mark_score(y, &count);//成功后记录步数
						mark_direction(direction, y);//记录方向
						break;
					}
				}
			}
			setcolor(hout, 0, 7);
			if (key != 'Q' && key != 'q' || y == check())
			{
				while (1)
				{
					if (y == check())
					{
						cout << "按“q”键退出！" << endl;
						key = _getch();
						if (key == 'q')
							break;
					}
					else
					{
						gotoxy(hout, 98, 34);
						cout << "成功！" << endl;
						gotoxy(hout, 97, 35);
						cout << "“q”键退出！" << endl;
						key = _getch();
						if (key == 'q')
							break;
					}
				}
			}
			system("cls");
			system("mode con cols=82 lines=25");
		}
		else if (key == '3')//子题目3
		{
			HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
			system("cls");
			system("mode con cols=110 lines=112");
			int count = 0;//步数
			print_choice(&y);//选择对应关卡
			findFile(a, y);//扫描对应文件并打开
			find_hang_lie(&s, &t, a);//计算行列数
			print_all(&s, &t, a);//打印界面
			setcolor(hout, 0, 7);
			if (y != check())
			{
				gotoxy(hout, 98, 33);
				setcolor(hout, 0, 7);
				cout << "步数：" << count;
			}
			int x1, y1, i = 1;
			find_s(&x1, &y1, &s, &t, a);//寻找初始启动位置
			update_b(b);//b清零
			mark_f(&s, &t, a, b); //记录特殊点的坐标
			if (y != check())
				find_answer(a, b, &x1, &y1, y, &key, &count, &s, &t, direction, &i);//读取答案文件并演示
			if (check_success(&s, &t, a) == 1 && y != check())//判断游戏是否成功
			{
				gotoxy(hout, 98, 34);
				cout << "成功！" << endl;
			}
			setcolor(hout, 0, 7);
			if (key != 'Q' && key != 'q' || y == check())
			{
				while (1)
				{
					if (y == check())
					{
						gotoxy(hout, 97, 35);
						cout << "“q”键退出！" << endl;
						key = _getch();
						if (key == 'q')
							break;
					}
					else
					{
						gotoxy(hout, 97, 35);
						cout << "“q”键退出！" << endl;
						key = _getch();
						if (key == 'q')
							break;
					}
				}
			}
			system("cls");
			system("mode con cols=82 lines=25");
		}
		else
			system("cls");
	}
	cout << endl;
	return 0;
}