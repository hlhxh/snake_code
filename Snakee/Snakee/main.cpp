#define _CRT_SECURE_NO_WARNINGS

//引入自定义头文件

#include"snake.h"


int main(void)
{
	//去除光标
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
   //函数引用
	srand(time(NULL));
	initSnake();
	initFood();
	initWall();
	initUI();
	playGame();       //启动游戏
	showscore();
	system("pause");
	return EXIT_SUCCESS;
}

void showscore(void)
{	//调整光标位置至不干扰游戏
	COORD coord;
	coord.X = 0;
	coord.Y = HIGH + 2;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("Game Over!!!\n");
	printf("成绩为：%d\n", score);
}

void initSnake(void)
{
	snake.size = 2;

	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;
	return;
}

//初始化界面控件
void initUI(void)
{
   
	COORD coord = { 0 };    //光标移动的位置

	//画蛇
	for (size_t i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;


		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

		if(i==0)
			putchar('@');
		else
			putchar('*'); 
	}

	//去除蛇尾
	coord.X = lastX;
	coord.Y = lastY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');
	//画食物
	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');



}

//食物位置
void initFood(void)
{
	//0-59
	food.X = rand() % WIDE ;
	food.Y = rand() % HIGH ;

}
void initWall(void)
{
	for (size_t i = 0; i <= HIGH; i++)
	{
		for (size_t j = 0; j <= WIDE; j++)
		{
			if (j == WIDE)
			{
				printf("|");
			}
			else if (i == HIGH)
			{
				printf("_");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void playGame(void)
{
	char key = 'd';
	//判断蛇撞墙
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		//更新蛇
		initUI();
		//接受用户按键，ASWD  
		if (_kbhit())
		{
			key = _getch();
		}
		//英文状态下小写才可以移动
		switch (key)
		{
		case'w':kx = 0; ky = -1; break;
		case's':kx = 0; ky = +1; break;
		case'd':kx = +1; ky = 0; break;
		case'a':kx = -1; ky = 0; break;
		default:
			break;
		}
		//蛇撞身体
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;//游戏结束
			}
		}
		//蛇头撞食物
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			//食物消失
			initFood();
			//身体增长
			snake.size++;
			//加分
			score += 10;
			//加速
			sleepSecond -= 20;
		}

		lastX = snake.body[snake.size - 1].X;
		lastY = snake.body[snake.size - 1].Y;

		//蛇移动，前一节身体给后一节身体赋值
		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;

		}
		//蛇头移动
		snake.body[0].X += kx;
		snake.body[0].Y += ky;




		//清屏
		//system("cls");

		Sleep(sleepSecond);
	}
	return;
}