#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define height 5
#define width 5
char map[5][5];
int posx, posy;
int score;
int coin;
int timer;
char *statuses[4] = {"running", "jumping", "crouching", "invincible"};

typedef struct
{
    int status; // 0 run 1 jump 2 down 3 无敌
} Role;

Role role;

void HideCursor();
void gotoxy(int x, int y);
void startup();
void LoseShow();
void show();
int updateWithIn();
void updateWithoutIn();
char generateObs();
int replay();
int isLoseOrGetCoin();
void updateState();

int main()
{

    HideCursor();
    while (replay())
    {
        srand(time(NULL));
        startup();
        while (1)
        {
            show();                      // 展示地图
            updateState();               // 更新状态
            int Break1 = updateWithIn(); // 用户输入 0 退出
            int Break2 = updateWithIn(); // 一帧里第二次输入
            updateWithoutIn();           // 更新地图

            int flag = isLoseOrGetCoin(); // 算分 0 die
            if (!(flag && Break1 && Break2))
            {
                LoseShow();
                break;
            }
        }
    }
}

void HideCursor() // 隐藏光标的函数的定义
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}

// 更新状态
void updateState()
{
    if (role.status == 1 || role.status == 2)
    {
        role.status = 0;
    }
}

/*
设置初始状态
隐藏光标
初始化玩家的分数和金币
设置角色的初始状态和位置
生成初始地图。
*/
void startup()
{
    score = 0;
    coin = 0;
    role.status = 0;
    timer = 0;
    posx = 2;
    posy = 4;
    for (int i = 0; i < height; i++)
    {
        int xcount = 0;
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
                map[i][j] = '|';
            else if (i == posy && j == posx)
                map[i][j] = ' ';
            else if (i < 2)
            {
                map[i][j] = generateObs();
                if (map[i][j] == 'X')
                    xcount++;
                if (xcount == 3)
                {
                    char ch = generateObs();
                    while (ch == 'X')
                        ch = generateObs();
                    map[i][j] = ch;
                }
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
}

// 获取随机字符
char generateObs()
{
    int chance = rand() % 50;
    if (chance < 10)
        return '$';
    else if (chance < 14)
        return 'D';
    else if (chance < 18)
        return 'U';
    else if (chance < 22)
        return '@';
    else if (chance < 26)
        return 'X';
    else
        return ' ';
}

/*
游戏渲染函数
用于在控制台中显示游戏的当前状态。
显示分数和金币
根据分数控制游戏速度。
*/
void show()
{
    gotoxy(0, 0);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == posy && j == posx)
            {
                printf("%c", 'o');
            }
            else
                printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("status: %12s\n", *(statuses + role.status));
    printf("Score: %6d | Coin: %4d", score, coin);

    if (score < 1000)
        Sleep(900);
    else if (score < 2000)
        Sleep(700);
    else if (score < 4000)
        Sleep(500);
    else
        Sleep(400);
}

/*
根据用户的键盘输入来更新游戏中的角色位置或状态。
用户通过按键控制角色的移动
并更改状态
同时提供了暂停/退出游戏
return 0 退出游戏
*/
int updateWithIn()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 'd')
        {
            if (posx != 3)
                posx++;
        }
        else if (input == 'a')
        {
            if (posx != 1)
                posx--;
        }
        else if (input == 'w')
        {
            if (role.status != 3)
                role.status = 1;
        }
        else if (input == 's')
        {
            if (role.status != 3)
                role.status = 2;
        }
        else if (input == 32) // 空格键 暂停
        {
            system("pause");
            updateWithIn();
        }
        else if (input == 27) // Esc 退出
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

/*
在没有用户输入的情况下
用于更新游戏状态的函数
*/
void updateWithoutIn()
{
    if (role.status == 3 && timer == 0)
        role.status = 0;
    else
        timer--;
    for (int i = height - 1; i >= 0; i--)
    {
        int xcount = 0;
        for (int j = 1; j < width - 1; j++)
        {
            if (i == 0)
            {
                map[i][j] = generateObs();
                if (map[i][j] == 'X')
                    xcount++;
                if (xcount == 3)
                {
                    char ch = generateObs();
                    while (ch == 'X')
                        ch = generateObs();
                    map[i][j] = ch;
                }
            }
            // 地图滚动
            else
            {
                map[i][j] = map[i - 1][j];
            }
        }
    }
}

/*
积分函数
越过障碍物、获得$  加分
捡到@  设置无敌状态
return 0 游戏结束
return 1 游戏继续
*/
int isLoseOrGetCoin()
{
    if (map[posy][posx] == '$')
    {
        coin++;
        score += 50;
    }
    else if (map[posy][posx] == 'U')
    {
        if (role.status == 1 || role.status == 3)
            score += 100;
        else
            return 0;
    }
    else if (map[posy][posx] == 'D')
    {
        if (role.status == 2 || role.status == 3)
            score += 100;
        else
            return 0;
    }
    else if (map[posy][posx] == 'X')
    {
        if (role.status == 3)
            score += 100;
        else
            return 0;
    }
    else if (map[posy][posx] == '@')
    {
        role.status = 3;
        timer = 4;
    }
    return 1;
}

// 重新开始游戏或退出
int replay()
{
    system("cls");
    printf("Press 'Enter' to start.\n");
    printf("Press 'Esc' to exit.");
    char input;
    input = getch();
    // ENTER 13 继续游戏 ESC 27 退出游戏
    if (input == 13)
    {
        system("cls");
        return 1;
    }
    else if (input == 27)
    {
        system("cls");
        return 0;
    }
    else
    {
        return replay();
    }
}

// 每轮游戏结束分数展示
void LoseShow()
{
    system("cls");
    printf("Your score is %d.", score);
    Sleep(3000);
}
