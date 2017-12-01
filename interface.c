#include "strings.h"
#include "contact.h"
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

// 接受用户输入的字符串，字符串长度不超过length
void receive(char * str, int length)
{
    output(INPUT_HINT);
    int ch;
    for (int i = 1; i < length; i++)
    {
        if ((ch = getchar()) != '\n') *str++ = ch;
        else {
            *str++ = '\0'; 
            break;
        }
    }
    *str = '\0';
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

// 接受用户输入的数字
void int_input(int * num)
{
    while (output(INPUT_HINT), scanf("%d", num) == 0) eatline();
    eatline();
}

// 接受用户输入的字符串
void str_input(char * str)
{
    receive(str, BUFFER_LEN);
}

// 清屏
void clear_display(void)
{
    system("cls");
}

// 等待用户按下任意键继续
void pause_display(void)
{
    system("pause");
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

// 显示“添加记录”模块
void display_add_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_ADD); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“浏览记录”模块
void display_show_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_SHOW); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“删除记录”模块
void display_delete_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_DELETE); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“查询记录”模块
void display_query_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_QUERY); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
    output("1"); output(SLASH); output(QUERY_BY_NAME); output(NEW_LINE);
    output("2"); output(SLASH); output(QUERY_BY_AGE); output(NEW_LINE);
    output("3"); output(SLASH); output(QUERY_BY_PHONE); output(NEW_LINE);
    output("4"); output(SLASH); output(QUERY_BY_EMAIL); output(NEW_LINE);
    output("5"); output(SLASH); output(QUERY_BY_ADDRESS); output(NEW_LINE);
    output("0"); output(SLASH); output(UPPER_MODULE); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“修改记录”模块
void display_modify_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_MODIFY); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“保存记录”模块
void display_save_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_SAVE); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示“排序记录”模块
void display_sort_module(void)
{
    output(PROJECT_NAME); output(SLASH); output(MODULE_SORT); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);

    output("1"); output(SLASH); output(SORT_BY_NAME); output(NEW_LINE);
    output("2"); output(SLASH); output(SORT_BY_AGE); output(NEW_LINE);
    output("0"); output(SLASH); output(UPPER_MODULE); output(NEW_LINE);
    output(BANNER); output(NEW_LINE);
}

// 显示退出消息
void goodbye(void)
{
    output(GOODBYE);
    exit(0);
}
