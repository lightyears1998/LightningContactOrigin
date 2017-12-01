#include "main.h"
#include "contact.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Person person[CAPACITY_LIMIT];
int extremity;

// 从文件中获取保存的联系人信息
void init()
{
    FILE * fp = fopen("info.csv", "r");
    if (fp == NULL) return;
    
    char buf[BUFFER_LEN];
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        person[extremity].guid = extremity;
        strncpy(person[extremity].name, buf, strlen(buf) - 1);
        fgets(buf, sizeof(buf), fp);
        person[extremity].age = atoi(buf);
        fgets(buf, sizeof(buf), fp);
        strncpy(person[extremity].number, buf, strlen(buf) - 1);
        fgets(buf, sizeof(buf), fp);
        strncpy(person[extremity].email, buf, strlen(buf) - 1);
        fgets(buf, sizeof(buf), fp);
        strncpy(person[extremity].address, buf, strlen(buf) - 1);
        extremity++;
    }

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
}

// 删除记录
void delete_record()
{
    display_delete_module();
    if (extremity == 0) {
        printf("当前系统中没有联系人信息，不能执行删除操作\n");
        return;
    }

    while (true)
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
            printf("确认删除？");
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
                printf("联系人已成功删除\n");
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
    while (true)
    {
        display_query_module();   
        switch (limited_input('0', '5'))
        {
            case '0': {
                clear_display();
                return;
            }
            case '1': query_by_name(); break;
            case '2': query_by_age(); break;
            case '3': query_by_phone(); break;
            case '4': query_by_email(); break;
            case '5': query_by_address(); break;
        }
    }
}

// 以姓名为关键词查询记录
void query_by_name(void)
{

}

// 以年龄为关键词查询记录
void query_by_age(void)
{

}

// 以手机为关键词查询记录
void query_by_phone(void)
{

}

// 以电邮为关键词查询记录
void query_by_email(void)
{

}

// 以地址为关键词查询记录
void query_by_email(void)
{

}

// 修改记录
void modify_record()
{
    display_modify_module();
    while (true)
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
        
            clear_display();
            printf("联系人“%s”已修改\n", person[guid].name);
            pause_display();
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

// 排序记录
void sort_record()
{
    display_sort_module();
}
