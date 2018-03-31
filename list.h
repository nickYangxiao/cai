#ifndef _LIST_H_
#define _LIST_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>


//用户信息结构
typedef struct userInfo
{
    char name[32];      //账号
    int passwd;         //密码
    int balance;       //余额
    long lottID;        //彩票ID
    char type[36];      //彩票类型
    int amount;         //购买数量
    bool state;         //开奖状态
}userInfo;

//用户节点结构
typedef struct userNode
{  
    struct userInfo data;
    struct userNode *pNext;
}userNode;

//彩票信息结构
typedef struct lottInfo
{
    char name[32];       //管理员账户
    int pwd;             //管理员密码
    long lottID;        //ID
    char type[36];      //彩票类型
    int price;          //彩票单价
    int amount;         //认购数量
    bool state;         //状态
    char startime[36];    //发布时间
    char endtime[36];	//开奖时间
}lottInfo;

//彩票节点结构
typedef struct lottNode
{
    struct lottInfo data;
    struct lottNode *pNext;
}lottNode;


//宏定义用户信息结构长度
#define USERINFO_LEN sizeof(struct userInfo)
//宏定义用户信息节点结构长度
#define USERNODE_LEN sizeof(struct userNode)

//宏定义彩票信息结构长度
#define LOTTINFO_LEN sizeof(struct lottInfo)
//宏定义彩票信息节点结构长度
#define LOTTNODE_LEN sizeof(struct lottNode)


//服务端功能
//创建彩票节点
lottNode *makeNode();
//获取管理员信息
int getAdminData(lottInfo *temp);
//添加管理员信息-------管理员注册
int add_admin(lottNode *pHead, lottInfo data);
//彩票数据录入
int getData(lottInfo *temp);
//发布彩票
int add_lott(lottNode *pHead, lottInfo data);
//按ID删除彩票
int del_lott(lottNode *pHead, long lottID);
//按ID查询彩票信息
lottNode *lookupUser(lottNode *pHead, long lottID);
//按帐号余额有序显示彩民（未排序）
void showAllUser(userNode *pHead);
//保存数据
void writeToFile(lottNode *pHead);
//加载数据
lottNode *readFromFile();

//客户端功能
//分配空间
userNode *makeUserNode();
//获取用户信息
int getUserData(userInfo *temp);
//添加用户----注册
int add_user(userNode *pHead, userInfo data);
//保存数据
void writeFile(userNode *pHead);
//加载数据
userNode *readFile();


#endif




















