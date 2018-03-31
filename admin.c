#include "./admin.h"
#include "./public.h"
#include "./interfaceUI.h"

//管理员注册
int AdminRegister(lottNode *pHead)
{
	lottInfo data;
	lottNode *temp = pHead->pNext;
	memset(&data, '\0', LOTTINFO_LEN);
	getAdminData(&data);
	pHead = readFromFile();
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
                AdminRegister(pHead);
                return 1;
            }
            else
            {
                adminlogin(pHead);
                return 1;
            }
        }
        temp = temp->pNext;
    }
	if(NULL == temp)
	{
	    printf("\n\t注册成功！\n");
        sleep(1);
        system("clear");
        add_admin(pHead, data);
        writeToFile(pHead);
        adminlogin(pHead);
	}
	return 1;
}

//管理员登录
int adminlogin(lottNode *pHead)
{
	lottInfo data;
	lottNode *temp = pHead->pNext;
	memset(&data, '\0', LOTTINFO_LEN);
	printf("\n\t***********管理员登录***************");
	printf("\n\t帐号：");
	mygets(data.name, sizeof(data.name));
	printf("\n\t密码：");
	data.pwd = myscanf();
	pHead = readFromFile();
	while(NULL != temp)
    {
       if(strcmp(temp->data.name, data.name) == 0 && data.pwd == temp->data.pwd)
       {
            printf("\n\t登录成功\n");
            sleep(1);
            system("clear");
            adminFunc(pHead);
            return 1;
       }
       temp = temp->pNext;
    }
	if(NULL == temp)
    {
        printf("\n\t用户名或密码错误！");
        printf("\n");
        printf("\n\t1.注册    2.重新输入");
        printf("\n\t请选择：");
        int ch = myscanf();
        if(ch == 1)
		{
			system("clear");
			AdminRegister(pHead);
			return 1;
		}
		else
		{
			system("clear");
			adminlogin(pHead);
			return 1;
		}
    }
    return 1;
}


//添加彩票
int addFunc(lottNode *pHead)
{
    pHead = readFromFile();
    lottNode *temp = pHead->pNext;
    lottInfo data;
    memset(&data, '\0', LOTTINFO_LEN);
    getData(&data);
    while(NULL != temp)
    {
        if(temp->data.lottID == data.lottID)
        {
            printf("\t彩票编号相同，请重新输入！\n");
            sleep(1);
            adminFunc(pHead);
            return 0;
        }
        temp = temp->pNext;
    }
	if(NULL == temp)
    {
		add_lott(pHead, data);
		writeToFile(pHead);
		printf("\t添加成功！\n");
		sleep(1);
		adminFunc(pHead);
		return 0;
	}
    return 0;
}

//按彩票ID删除彩票
int delFunc(lottNode *pHead)
{
    pHead = readFromFile();
	lottNode *temp = pHead->pNext;
	long lottID = 0;
    printf("\t输入彩票ID: ");
    lottID = myscanf();
    while(NULL != temp)
    {
        if(temp->data.lottID == lottID)
        {
            del_lott(pHead, lottID);
            printf("\n\t删除成功\n");
            writeToFile(pHead);
            sleep(1);
            adminFunc(pHead);
            return 0;
        }
        temp = temp->pNext;
    }
    if(NULL == temp)
    {
        printf("\n\t彩票不存在!\n");
        sleep(1);
		adminFunc(pHead);
		return 0;
    }
    return 0;
}

//按彩票ID查询彩票信息
int checkFunc(lottNode *pHead)
{
	long lottID = 0;
	char getch = '0';
    printf("\t输入彩票ID: ");
    lottID = myscanf();
    lottNode *p = lookupUser(pHead,lottID);
    if(NULL != p)
    {
        printf("\tID\t类型\t\t单价\t已售数量\t状态\t发布时间\t开奖时间\n");
        printf("\t%ld\t%s\t%d\t%d\t\t%d\t%s\t\t%s\n", p->data.lottID, p->data.type, p->data.price,p->data.amount,p->data.state,p->data.startime,
												  p->data.endtime);
		printf("\n\t按ENTER键继续.....");
		scanf("%c",&getch);
		if(getch == '\n')
		{
			adminFunc(pHead);
			return 0;
		}

    }
    else
    {
		printf("\n\t彩票不存在!\n");
        sleep(1);
		adminFunc(pHead);
		return 0;
    }
	return 0;
}

//按帐号余额有序显示彩民
void showAllUser(userNode *pHead)
{
    char getch = '0';
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return;
    }
    pHead = readFile();
    userNode *p = pHead->pNext;
    printf("\n\t帐号\t\t余额\n\t");
    while(NULL != p)
    { 
        printf("\n\t%s\t%d\n", p->data.name, p->data.balance);
        p = p->pNext;
    }
    printf("\n\t按ENTER键继续.....");
	scanf("%c",&getch);
	if(getch == '\n')
	{
		adminFunc(pHead);
		return;
    }
    return;
}

//开奖------管理员指定彩票ID
int openFunc(lottNode *pHead)
{
    char getch = '0';
    pHead = readFromFile();
    lottNode *temp = pHead->pNext;
    userNode *pHead1 = readFile();
    userNode *temp1 =  pHead1->pNext; 
    printf("\n\t请输入中奖彩票ID： ");
    long ID = myscanf();
    while(NULL != temp)
    {
        if(temp->data.lottID == ID)
        {
            printf("\n\t开奖成功！\n");
           temp->data.state = true;
            writeToFile(pHead);
            while(NULL != temp1)
            {
                if(temp1->data.lottID == ID)
                {
                    temp1->data.state = temp->data.state;
                    temp1->data.balance += 1000 * temp1->data.amount;
                    writeFile(pHead1);
                    printf("\n\t按ENTER键继续.....");
	                scanf("%c",&getch);
	                if(getch == '\n')
	                {
		                adminFunc(pHead);
		                return 0;
	                }
                    return 1;
                } 
                temp1 = temp1->pNext;               
            }
            if(NULL == temp1)
            {
                return 0;
            }
        }
        temp = temp->pNext;
    }
	return 1;
}

int adminloginMenu(lottNode *pHead)
{
    system("clear");
    adminloginUI();
    int choice = myscanf();
    switch(choice)
    {
        case 1:
        {
            AdminRegister(pHead);
            break;
        }
        case 2:
        {
            adminlogin(pHead);
            break;
        }
    }
    return 1;
}

int adminFunc()
{
    lottNode *pHead = readFromFile();
    userNode *pHead1 = readFile();
	system("clear");
    adminUI();
    int choice = myscanf();
    switch(choice)
    {
		case 1:
		{
	   		addFunc(pHead);
	    	break;
		}
		case 2:
		{
			delFunc(pHead);
			break;
		}
		case 3:
		{
			checkFunc(pHead);
			break;
		}
		case 4:
		{
            showAllUser(pHead1);
			break;
		}
        case 5:
        {
            openFunc(pHead);
            break;
        }
		case 0:
		{
	    	break;
		}
    }
	return 0;
}
