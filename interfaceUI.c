#include "./interfaceUI.h"

#include<stdio.h>

void mainUI()
{
    printf("\t1. 管理员登录\n");
    printf("\n");
    printf("\t2. 用户登录\n");
    printf("\n");
    printf("\t0. 退出\n");
    printf("\n");
    printf("\t请选择：");
}

void adminloginUI()
{
    printf("\t1. 管理员注册\n");
    printf("\t2. 管理员登录\n");
	printf("\t请选择：");
    return;
}

void adminUI()
{
    printf("\t1. 发布彩票\n");
    printf("\t2. 删除彩票\n");
    printf("\t3. 查询彩票信息\n");
    printf("\t4. 显示所有彩民\n");
	printf("\t5. 开奖\n");
    printf("\t0. 退出\n");
    printf("\t请选择: ");
    return;
}

void userloginUI()
{
    printf("\t1. 用户注册\n");
    printf("\t2. 用户登录\n");
	printf("\t请选择：");
    return;
}

void userUI()
{
    printf("\t1. 个人资料\n");
    printf("\t2. 购买彩票\n");
    printf("\t3. 购彩记录\n");
    printf("\t4. 余额充值\n");
    printf("\t5. 修改密码\n");
    printf("\t0. 退出\n");
    printf("\t请选择: ");
    return;
}

