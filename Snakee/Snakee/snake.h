#pragma once
//报错
//#ifndef__SNAKE_H__
//#define__SNAKE_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>

#define WIDE 60
#define HIGH 20

struct BODY {
	int X;
	int Y;
};

struct SNAKE {
	struct BODY body[WIDE * HIGH];
	int size;
}snake;

struct FOOD {
	int X;
	int Y;
}food;

int score = 0;

int kx = 0;  //用户按下ASDW任意一个按键所得到的坐标值
int ky = 0;

int lastX = 0;  //蛇尾的坐标
int lastY = 0;

int sleepSecond=300;


//函数声明
void initSnake(void);
void initFood(void);
void initUI(void);
void playGame(void);
void initWall(void);
void showscore(void);


//#endif