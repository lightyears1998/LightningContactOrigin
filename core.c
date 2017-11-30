#include "contact.h"
#include "interface.h"
#include <stdio.h>
#include <stdbool.h>
#define CAPACITY_LIMIT 80

struct Person person[CAPACITY_LIMIT];
int extremity;

// 从文件中获取保存的联系人信息
void init()
{
    FILE * fp = fopen("info.csv", "r");
    if (fp == NULL) return;
    
    fclose(fp);
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

    printf("姓名："); str_input(person[extremity].name);
    printf("年龄："); int_input(&person[extremity].age);
    printf("电话："); long_input(&person[extremity].number);
    printf("电邮："); str_input(person[extremity].email);
    printf("地址："); str_input(person[extremity].address);

    clear_display();
    printf("新的联系人“%s”已添加到系统中\n", person[extremity].name);
    
    extremity++;
}

// 显示特定联系人的信息
void show_person(struct Person * p)
{
    printf("姓名：%s\n", p -> name);
    printf("年龄：%d\n", p -> age);
    printf("电话：%lld\n", p -> number);
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

    for (int i = 0; i < extremity; i++) show_person(&person[i]);
}

// 删除记录
void delete_record()
{
    display_delete_module();
    if (extremity == 0) {
        printf("当前系统中没有联系人信息，不能执行删除操作\n");
        return;
    }
}

// 查询记录
void query_record()
{
    display_query_module();
}

// 修改记录
void modify_record()
{
    display_modify_module();
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
            "%s,%d,%lld,%s,%s\n",
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
}

// 排序记录
void sort_record()
{
    display_sort_module();
}
