/** 
 * 将大部分功能压缩到500行左右代码的紧凑实现
 * 小项目其实不需要太复杂的项目体系
**/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define BUFFER_LEN 1024
#define CAPACITY_LIMIT 80

void add_record();
void show_record();
void delete_record();
void query_record();
void modify_record();
void save_record();

void query_by_name();
void query_by_age();
void query_by_number();
void query_by_email();
void query_by_address();

void eatline();
int input();
void receive(char *, int);
int limited_input(int, int);
void int_input(int *);
void str_input(char *);

void clear_display();
void pause_display();
void output(const char *);

void display_main_menu();
void display_add_module();
void display_show_module();
void display_delete_module();
void display_query_module();
void display_modify_module();
void display_save_module();
void display_sort_module();
void goodbye();

void call_module(int);

struct Person
{
    int guid;
    char name[BUFFER_LEN];
    int age;
    char number[BUFFER_LEN];
    char email[BUFFER_LEN];
    char address[BUFFER_LEN];
};

struct Person person[CAPACITY_LIMIT];
int extremity;

int main()
{
    while (1)
    {
        display_main_menu();
        call_module(limited_input('0', '6') - '0');
    }
    return 0;
}

void call_module(int idx)
{
    clear_display();
    switch (idx)
    {
        case 0: goodbye(); break;
        case 1: add_record(); break;
        case 2: show_record(); break;
        case 3: delete_record(); break;
        case 4: query_record(); break;
        case 5: modify_record(); break;
        case 6: save_record(); break;
    }
}

// 添加记录
void add_record()
{
    display_add_module();
    
    if (extremity + 1 > CAPACITY_LIMIT) {
        clear_display();
        printf("内存已满，不能再添加新的联系人\n");
        return;
    }

    printf("正在添加第%d位联系人\n", extremity + 1);

    person[extremity].guid = extremity;
    printf("姓名："); str_input(person[extremity].name);
    printf("年龄："); int_input(&person[extremity].age);
    printf("电话："); str_input(person[extremity].number);
    printf("电邮："); str_input(person[extremity].email);
    printf("地址："); str_input(person[extremity].address);

    clear_display();
    printf("新的联系人“%s”已添加到系统中\n", person[extremity].name);
    
    extremity++;
}

// 显示特定联系人的信息
void show_person(int guid)
{
    struct Person * p = &person[guid];
    printf("姓名：%s (#%d)\n", p -> name, p -> guid);
    printf("年龄：%d\n", p -> age);
    printf("电话：%s\n", p -> number);
    printf("电邮：%s\n", p -> email); 
    printf("地址：%s\n", p -> address);
    printf("--------------------------------\n");
}

// 浏览记录
void show_record()
{
    display_show_module();

    if (extremity == 0) {
        printf("当前系统中没有联系人信息\n");
        pause_display();
        clear_display();
        return;
    }

    for (int i = 0; i < extremity; i++) show_person(i);
    pause_display();
    clear_display();
}

// 删除记录
void delete_record()
{
    display_delete_module();
    if (extremity == 0) {
        printf("当前系统中没有联系人信息，不能执行删除操作\n");
        return;
    }

    while (1)
    {
        printf("请指定欲删除联系人的GUID：");
        int guid; int_input(&guid);
        if (guid < 0) {
            printf("删除操作已取消\n");
            pause_display();
            clear_display();
            return;
        }
        else if (guid >= extremity) {
            printf("该GUID对应的联系人不存在\n");
        }
        else {
            show_person(guid);
            printf("请确认删除 (Y/N) ");
            char buf[BUFFER_LEN]; str_input(buf);
            if (buf[0] == 'Y' || buf[0] == 'y') {
                for (int i = guid; i < extremity - 1; i++)
                {
                    strncpy(person[i].name, person[i + 1].name, BUFFER_LEN - 1);
                    person[i].age = person[i + 1].age;
                    strncpy(person[i].number, person[i + 1].number, BUFFER_LEN - 1);
                    strncpy(person[i].email, person[i + 1].email, BUFFER_LEN - 1);
                    strncpy(person[i].address, person[i + 1].address, BUFFER_LEN - 1);
                }
                extremity--;
                printf("成功删除联系人\n");
                pause_display();
                clear_display();
                return;
            }
            else {
                printf("删除操作已取消\n");
                pause_display();
                clear_display();
                return;
            }
        }
    }
}

// 查询记录
void query_record()
{
    while (1)
    {
        display_query_module();   
        
        int oprt = limited_input('0', '5');
        clear_display();
        switch (oprt)
        {
            case '0': return;
            case '1': query_by_name(); break;
            case '2': query_by_age(); break;
            case '3': query_by_number(); break;
            case '4': query_by_email(); break;
            case '5': query_by_address(); break;
        }
        pause_display();
        clear_display();
    }
}

// 以姓名为关键词查询记录
void query_by_name()
{
    char buf[BUFFER_LEN]; 
    printf("请键入欲查询的姓名："); str_input(buf);
    
    int found = 0;
    for (int i = 0; i < extremity; i++)
    {
        if (strstr(person[i].name, buf) != NULL) {
            show_person(i);
            found = 1;
        }
    }
    if (!found) printf("没有找到与“%s”相关的联系人\n", buf);
}

// 以年龄为关键词查询记录
void query_by_age()
{
    int age; 
    printf("请键入欲查询的年龄："); int_input(&age);
    
    int found = 0;
    for (int i = 0; i < extremity; i++)
    {
        if (person[i].age == age) {
            show_person(i);
            found = 1;
        }
    }
    if (!found) printf("没有找到年龄为%d的联系人\n", age);
}

// 以手机为关键词查询记录
void query_by_number()
{
    char buf[BUFFER_LEN]; 
    printf("请键入欲查询的电话："); str_input(buf);
    
    int found = 0;
    for (int i = 0; i < extremity; i++)
    {
        if (strstr(person[i].number, buf) != NULL) 
        {
            show_person(i);
            found = 1;
        }
    }
    if (!found) printf("没有找到与“%s”相关的联系人\n", buf);
}

// 以电邮为关键词查询记录
void query_by_email()
{
    char buf[BUFFER_LEN]; 
    printf("请键入欲查询的电邮："); str_input(buf);
    
    int found = 0;
    for (int i = 0; i < extremity; i++)
    {
        if (strstr(person[i].email, buf) != NULL) {
            show_person(i);
            found = 1;
        }
    }
    if (!found) printf("没有找到与“%s”相关的联系人\n", buf);
}

// 以地址为关键词查询记录
void query_by_address()
{
    char buf[BUFFER_LEN]; 
    printf("请键入欲查询的地址："); str_input(buf);
    
    int found = 0;
    for (int i = 0; i < extremity; i++)
    {
        if (strstr(person[i].address, buf) != NULL) {
            show_person(i);
            found = 1;
        }
    }
    if (!found) printf("没有找到与“%s”相关的联系人\n", buf);
}

// 修改记录
void modify_record()
{
    display_modify_module();
    while (1)
    {
        printf("请指定欲修改的联系人的编号：");
        int guid; int_input(&guid);
        if (guid < 0)
        {
            printf("修改操作已取消\n");
            pause_display();
            clear_display();
            return;
        }
        else if (guid >= extremity)
        {
            printf("对应GUID的联系人不存在\n");
        }
        else
        {
            printf("正在修改联系人“%s”\n", person[guid].name);
            
            printf("姓名："); str_input(person[guid].name);
            printf("年龄："); int_input(&person[guid].age);
            printf("电话："); str_input(person[guid].number);
            printf("电邮："); str_input(person[guid].email);
            printf("地址："); str_input(person[guid].address);
        
            printf("联系人“%s”已修改\n", person[guid].name);
            pause_display();
            clear_display();
            return;
        }
    }
}

// 保存记录到文件
void save_record()
{
    display_save_module();
    
    FILE * fp = fopen("info.csv", "w");
    
    if (!fp) {
        printf("无法保存到文件\n");
        pause_display();
        clear_display();
        return;
    }
    
    for (int i = 0; i < extremity; i++)
    {
        int status = fprintf(
            fp,
            "%s\n%d\n%s\n%s\n%s\n",
            person[i].name,
            person[i].age,
            person[i].number,
            person[i].email,
            person[i].address
        );
        if (status > 0) continue;
        else {
            printf("保存文件时发生意外\n");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("记录已成功保存\n");

    pause_display();
    clear_display();
}

// 丢弃一行输入，避免使用者乱砸键盘导致意外
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
int input()
{
    int ch;
    while (1)
    {
        output(">> ");
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
    output(">> ");
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
    while (1)
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
    while (output(">> "), scanf("%d", num) == 0) eatline();
    eatline();
}

// 接受用户输入的字符串
void str_input(char * str)
{
    receive(str, BUFFER_LEN);
}

// 清屏
void clear_display()
{
    system("cls");
}

// 等待用户按下任意键继续
void pause_display()
{
    system("pause");
}

// 显示主菜单
void display_main_menu()
{
    output("联系人管理系统"); output(" - "); output("主菜单"); output("\n");
    output("================================"); output("\n");

    output("1"); output(" - "); output("添加记录"); output("\n");
    output("2"); output(" - "); output("浏览记录"); output("\n");
    output("3"); output(" - "); output("删除记录"); output("\n");
    output("4"); output(" - "); output("查询记录"); output("\n");
    output("5"); output(" - "); output("修改记录"); output("\n");
    output("6"); output(" - "); output("保存记录"); output("\n");
    output("7"); output(" - "); output("排序记录"); output("\n");
    output("0"); output(" - "); output("退出程序"); output("\n");
    output("================================"); output("\n");
}

// 显示“添加记录”模块
void display_add_module()
{
    output("联系人管理系统"); output(" - "); output("添加记录"); output("\n");
    output("================================"); output("\n");
}

// 显示“浏览记录”模块
void display_show_module()
{
    output("联系人管理系统"); output(" - "); output("浏览记录"); output("\n");
    output("================================"); output("\n");
}

// 显示“删除记录”模块
void display_delete_module()
{
    output("联系人管理系统"); output(" - "); output("删除记录"); output("\n");
    output("================================"); output("\n");
}

// 显示“查询记录”模块
void display_query_module()
{
    output("联系人管理系统"); output(" - "); output("查询记录"); output("\n");
    output("================================"); output("\n");
    output("1"); output(" - "); output("查询姓名"); output("\n");
    output("2"); output(" - "); output("查询年龄"); output("\n");
    output("3"); output(" - "); output("查询电话"); output("\n");
    output("4"); output(" - "); output("查询邮件"); output("\n");
    output("5"); output(" - "); output("查询地址"); output("\n");
    output("0"); output(" - "); output("返回上级菜单"); output("\n");
    output("================================"); output("\n");
}

// 显示“修改记录”模块
void display_modify_module()
{
    output("联系人管理系统"); output(" - "); output("修改记录"); output("\n");
    output("================================"); output("\n");
}

// 显示“保存记录”模块
void display_save_module()
{
    output("联系人管理系统"); output(" - "); output("保存记录"); output("\n");
    output("================================"); output("\n");
}

// 显示退出消息
void goodbye()
{
    output("再见 : )");
    exit(0);
}
