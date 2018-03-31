#include "./user.h"
#include "./interfaceUI.h"
#include "./public.h"
#include "./list.h"

//用户登录
userNode* login(userNode *pHead)
{
	userInfo data;
	userNode *temp = pHead->pNext;
	memset(&data, '\0', USERINFO_LEN);
	printf("\n\t***********用户登录***************");
	printf("\n\t帐号：");
	mygets(data.name, sizeof(data.name));
	printf("\n\t密码：");
	data.passwd = myscanf();
	pHead = readFile();
	while(NULL != temp)
    {
       if(strcmp(temp->data.name, data.name) == 0 && data.passwd == temp->data.passwd)
       {
            printf("\n\t登录成功\n");
            sleep(1);
            system("clear");
            judge(pHead);
            userMenu(temp->data.name);
            return NULL;
       }
       temp = temp->pNext;
    }
	if(NULL == temp)
    {
        printf("\n\t用户名或密码错误！");
        printf("\n");
        printf("\n\t1.注册    2.重新输入");
        printf("\n\t请选择：");
        int ch = 0;
		scanf("%d",&ch);
		getchar();
        if(ch == 1)
		{
			system("clear");
			Register(pHead);
			return NULL;
		}
		else
		{
			system("clear");
			login(pHead);
			return NULL;
		}
    }
    return NULL;
}

//用户注册
int Register(userNode *pHead)
{
	userInfo data;
	userNode *temp = pHead->pNext;
	memset(&data, '\0', USERINFO_LEN);
	getUserData(&data);
	pHead = readFile();
	while(NULL != temp)
    {
        if(strcmp(data.name, temp->data.name) == 0)
        {
            printf("\n\t该用户名已存在！");
            printf("\n\t是否继续注册（Y/N）：");
            char ch = '0';
            scanf("%c",&ch);
            if(ch == 'Y')
            {
                system("clear");
                Register(pHead);
                return 1;
            }
            else
            {
                login(pHead);
                return 1;
            }
        }
        else
        {
            temp = temp->pNext;
        }
    }
	if(NULL == temp)
	{
	    printf("\n\t注册成功！\n");
        sleep(1);
        system("clear");
        add_user(pHead, data);
        writeFile(pHead);
        login(pHead);
	}
		return 1;
}

//查询用户个人信息
int userData(char *name)
{
    userNode *pHead = readFile();
    userNode *temp = pHead->pNext;
    while(NULL != temp)
    {
        if(strcmp(temp->data.name, name) == 0)
        {
            printf("\n\t帐号\t余额\n\t");
            printf("\n\t%s\t%d\n\t", temp->data.name, temp->data.balance);
            printf("\n\t按ENTER键继续.....");
            char getch = '0';
            scanf("%c",&getch);
            if(getch == '\n')
            {
                userMenu(name);
                return 0;
            }
            return 1;
        }
        temp = temp->pNext;
    }
    return 0;
}

//购买彩票----按彩票ID购买
int buy_lott(char *name)
{
    int num = 0;
    userNode *pHead1 = readFile();
    userNode *temp1 = pHead1->pNext;
    lottNode *pHead2 = readFromFile();
    lottNode *temp2 = pHead2->pNext;
    printf("\n\t****************************可购彩票*******************************\n");
    printf("\n\tID\t类型\t\t单价\t已售数量\t状态\t发布时间\t开奖时间\n");
    while(NULL != temp2)
    {
        if(temp2->data.state != 0)
        {
            printf("\t%ld\t%s\t%d\t%d\t\t%d\t%s\t\t%s\n", temp2->data.lottID, temp2->data.type, temp2->data.price,temp2->data.amount,temp2->data.state,temp2->data.startime,
												  temp2->data.endtime);
        }
        temp2 = temp2->pNext;
    }
    if(temp2 == pHead2->pNext)
    {
        printf("\n\n\t当前无可购彩票，请稍后再试。。。。。\n");
        sleep(2);
        userMenu(name);
    }
    temp2 = pHead2->pNext;
    while(NULL != temp1)
    {
        if(strcmp(temp1->data.name, name) == 0)
        {
            printf("\n\t***************************购买彩票********************************\n");
            printf("\n\t请选择彩票ID： ");
            long ID = myscanf();
            while(NULL != temp2)
            {
                if(temp2->data.lottID == ID && temp2->data.state != 0)
                {
                    printf("\n\t请输入购买数量：");
                    scanf("%d",&num);
                    getchar();
                    if((temp1->data.balance) > (num*temp2->data.price) || (temp1->data.balance) == (num*temp2->data.price))
                    {
                        temp2->data.amount += num;
                        writeToFile(pHead2);
                        temp1->data.amount += num;
                        temp1->data.lottID = temp2->data.lottID;
                        strcpy(temp1->data.type, temp2->data.type);
                        temp1->data.state = temp2->data.state;
                        temp1->data.balance -= num * temp2->data.price;
                        writeFile(pHead1);
                        printf("\n\t购买成功,即将返回主界面。。。\n");
                        sleep(1);
                        userMenu(name);
                        return 1;
                    }
                    else
                    {
                        printf("\n\t余额不足，是否充值（y/n）:");
                        char choice = '0';
                        scanf("%c",&choice);
                        getchar();
                        if(choice == 'y')
                            add_bal(name);
                        else
                            userMenu(name);                            
                    }
                    return 1;
                }
                temp2 = temp2->pNext;
            }
            if(NULL == temp2) 
            {
                printf("\n\t您输入的ID有误！\n");
                sleep(2);
                userMenu(name);
                return 0;
            }
        }
        temp1 = temp1->pNext;
    }
    return 1;
}

//购彩记录
int  buy_record(char  *name)
{
    userNode *pHead = readFile();
    userNode *temp = pHead->pNext;
    printf("\n\t彩票ID\t类型\t\t数量\t状态\n");
    while(NULL != temp)
    {
        if(strcmp(temp->data.name, name) == 0)
        {
            printf("\n\t%ld\t%s\t%d\t%d\n", temp->data.lottID, temp->data.type, temp->data.amount, temp->data.state);
            printf("\n\t按ENTER键继续.....");
            char getch = '0';
            scanf("%c",&getch);
            if(getch == '\n')
            {
                userMenu(name);
                return 0;
            }
            return 0;
        }
        temp = temp->pNext;
    }
    return 0;
}


//余额充值
int add_bal(char *name)
{
    userInfo data;
    memset(&data, '\0', USERINFO_LEN);
    userNode *pHead = readFile();
    userNode *temp = pHead->pNext;
    while(NULL != temp)
    {
       if(strcmp(temp->data.name, name) == 0)
       {
           printf("\n\t请输入充值金额：");
           data.balance = myscanf();
           temp->data.balance += data.balance;
           writeFile(pHead);
           printf("\n\t充值成功，即将返回主界面。。。。\n");
           sleep(2);
           system("clear");
           userMenu(name);
           return 0;
       }
       temp = temp->pNext;
    }
    if(NULL == temp)
    {
        printf("\n\t充值失败。。。");
        return 0;
    }
    return 0;
}

//修改密码
int update_pwd(char *name)
{
     userNode *pHead = readFile();
     userNode *temp = pHead->pNext;
     userInfo data;
     memset(&data, '\0', USERINFO_LEN);
     while(NULL != temp)
     {
         if(strcmp(temp->data.name, name) == 0)
         {
             printf("\n\t请输入原密码： ");
             data.passwd = myscanf();
             if(data.passwd == temp->data.passwd)
             {
                 printf("\n\t请输入新密码：");
                 int pwd1 = myscanf();
                 if(pwd1 != temp->data.passwd)
                 {
                     printf("\n\t请确认新密码：");
                     int pwd2 = myscanf();
                     if(pwd1 == pwd2)
                     {

                         temp->data.passwd = pwd1;
                         system("clear");
                         printf("\n\t密码修改成功!\n");
                         sleep(1);
                         writeFile(pHead);
                         userMenu(name);
                         return 1;
                     }
                     else
                     {
                         system("clear");
                         printf("\n\t两次输入不同，即将返回......");
                         sleep(1);
                         update_pwd(name);
                         return 0;
                     }
                 }
                 else
                 {
                     system("clear");
                     printf("\n\t新密码与原密码相同，请重新输入......");
                     update_pwd(name);
                     return 0;
                 }
             }
             else
             {
                 printf("\n\t密码错误，请重新输入.....");
                 update_pwd(name);
                 return 0;
             }
         }
         temp = temp->pNext;
     }
     return 0;   
}


//判断是否中奖
int judge(userNode *pHead)
{
    pHead = readFile();
    userNode *temp = pHead->pNext;
   // printf("%s\n", name);
    while(NULL != temp)
    {
        //printf("%s\n", name);
        if(temp->data.state == true)
        {
           // system("clear");
            printf("\n\t\t\t\t恭喜中奖！\n");
            printf("\n\t中 奖 彩 票  ID：  %ld\n", temp->data.lottID);
            printf("\n\t中  奖  金  额 ：   %d\n", temp->data.amount * 1000);
            sleep(2);
            userMenu(pHead->data.name);
            return 1;
        }
        temp = temp->pNext;        
    }
    if(NULL == temp)
    {
        userMenu(pHead->data.name);
        return 0;
    }
    return 1;
}


int userMenu(char *name)
{
    system("clear");
    userUI();
    int choice = myscanf();
	switch(choice)
	{
        case 1:
        {
            userData(name);
            break;
        }
        case 2:
        {
            buy_lott(name);
            break;
        }
        case 3:
        {
            buy_record(name);
            break;
        }
        case 4:
        {
            add_bal(name);
            break;
        }
        case 5:
        {
            update_pwd(name);
            break;
        }
        case 0:
        {
            break;
        }
	}
	return 1;
}

