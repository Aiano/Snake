#include <Windows.h>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <time.h>
#include <cstdlib>

const int delaytime = 500;
const int mapsize = 10;
char map[mapsize + 1][mapsize + 1];
int mapinc[mapsize + 1][mapsize + 1][2];
int headx = 5, heady = 5;
int tailx = 5, taily = 4;
int inc[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int headCondition = 1;
int size = 2;
int y, x;

int main()
{
	memset(map, '.', sizeof(map));
	map[heady][headx] = '@';
	map[taily][tailx] = '#';
	do
	{
		y = rand() % mapsize + 1;
		x = rand() % mapsize + 1;
	} while (map[y][x] != '.');
	map[y][x] = '*';

	mapinc[taily][tailx][0] = heady; mapinc[taily][tailx][1] = headx;
	std::cout << "贪吃蛇 Version1.0 Made by Aiano_czm" << std::endl;
	std::cout << "w：上 s：下 a：左 d：右" << std::endl;
	std::cout << "p：暂停 esc：结束 （记得开英文输入）" << std::endl;
	for (int i = 1; i <= mapsize; i++)
	{
		for (int j = 1; j <= mapsize; j++)
			std::cout << map[i][j];
		std::cout << std::endl;
	}
	Sleep(delaytime);//初始状态

	time_t timeBegin = time(0);
	char a; bool b=true;
	
	while (1)
	{
		if (b==true && time(0) - timeBegin <= (delaytime / 1000))
		{
			if (_kbhit())
			{
				a = _getch();
				switch (a)
				{
				case 'w':if (headCondition == 1)break; else headCondition = 0; break;
				case 's':if (headCondition == 0)break; else headCondition = 1; break;
				case 'a':if (headCondition == 3)break; else headCondition = 2; break;
				case 'd':if (headCondition == 2)break; else headCondition = 3; break;
				case'p':std::cout << "Stop!" << std::endl; timeBegin += time(0) - timeBegin; system("pause"); break;
				case 27:std::cout << "Exit!" << std::endl; system("pause"); return 0;
				default:
					break;
				}
				b = false;
			}
		}
		else if(time(0) - timeBegin > (delaytime / 1000))
		{
			timeBegin = time(0);
			b = true;

			map[heady][headx] = '#';
			y = heady + inc[headCondition][0];
			x = headx + inc[headCondition][1];
			if (y < 1)y = mapsize;
			else if (y > mapsize)y = 1;
			if (x < 1)x = mapsize;
			else if (x > mapsize)x = 1;
			if (map[y][x] == '#') {
				std::cout << "Game over!" << std::endl;
				std::cout << "The size of snake is " << size << "."<<std::endl;
				system("pause");
				return 0;
			}if (map[y][x] == '*') {
				map[y][x] = '@';
				mapinc[heady][headx][0] = y; mapinc[heady][headx][1] = x;
				heady = y; headx = x;
				size++;
				do
				{
					y = rand() % mapsize + 1;
					x = rand() % mapsize + 1;
				} while (map[y][x] != '.');
				map[y][x] = '*';
			}
			else
			{
				map[y][x] = '@';
				mapinc[heady][headx][0] = y; mapinc[heady][headx][1] = x;
				heady = y; headx = x;
				y = taily; x = tailx;
				map[y][x] = '.';
				taily = mapinc[y][x][0];
				tailx = mapinc[y][x][1];
			}


			system("cls");
			std::cout << "贪吃蛇 Version1.0 Made by Aiano_czm" << std::endl;
			std::cout << "w：上 s：下 a：左 d：右" << std::endl;
			std::cout << "p：暂停 esc：结束 （记得开英文输入）" << std::endl;
			for (int i = 1; i <= mapsize; i++)
			{
				for (int j = 1; j <= mapsize; j++)
					std::cout << map[i][j];
				std::cout << std::endl;
			}
		}

	}


	return 0;
}

