#include "strings.h"

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// 丢弃一行输入
void eatline()
{
    int ch;
    while (ch = getchar(), ch != '\n' && ch != EOF);
}

// 向屏幕输出字符
void output(const char * str)
{
    printf("%s", str);
}

// 获取用户输入的字符
int input(void)
{
    int ch;
    while (true)
    {
        output(INPUT_HINT);
        ch = getchar();
        if (isspace(ch)) continue;
        else break;
    }
    eatline();
    return ch;
}

// 将用户输入的字符限定在指定范围
int limited_input(int bottom, int top)
{
    int ch;
    while (true)
    {
        ch = input();
        if (ch >= bottom && ch <= top) break;
        else continue;
    }
    return ch;
}

// 接受用户输入的字符串，字符串长度不超过length
void receive(char * str, int length)
{
    int ch;
    for (int i = 1; i < length; i++)
    {
        if ((ch = getchar()) != '\n') *str++ = ch;
        else *str++ = '\0';
    }
    *str = '\0';
}

// 清屏
void clear_display(void)
{
    system("cls");
}

// 显示主菜单
void display_main_menu(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_MAIN_MENU); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);

    output("1"); output(SLASH); output(MODULE_ADD); output(NEW_LINE);
    output("2"); output(SLASH); output(MODULE_SHOW); output(NEW_LINE);
    output("3"); output(SLASH); output(MODULE_DELETE); output(NEW_LINE);
    output("4"); output(SLASH); output(MODULE_QUERY); output(NEW_LINE);
    output("5"); output(SLASH); output(MODULE_MODIFY); output(NEW_LINE);
    output("6"); output(SLASH); output(MODULE_SAVE); output(NEW_LINE);
    output("7"); output(SLASH); output(MODULE_SORT); output(NEW_LINE);
    output("0"); output(SLASH); output(MODULE_EXIT); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

void goodbye(void)
{
    output(GOODBYE);
    exit(0);
}
