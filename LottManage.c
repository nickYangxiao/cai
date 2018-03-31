#include "./user.h"
#include "./interfaceUI.h"
#include "./public.h"
#include "./list.h"
#include "./admin.h"


int adminLoginMenu(lottNode *pHead)
{
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
        case 0:
        {
            break;
        }
    }
	return 1;
}

int loginMenu(userNode *pHead)
{
    int choice = myscanf();
    switch(choice)
    {
        case 1:
        {
			Register(pHead);
            break;
        }
        case 2:
        {
            login(pHead);
            break;
        }
        case 0:
        {
            break;
        }
    }
	return 1;
}

int mainMenu()
{
    lottNode *pHead1 = readFromFile();
    userNode *pHead2 = readFile();
    system("clear");
    mainUI();
    int choice = myscanf();
    switch(choice)
    {
        case 1:
        {
            system("clear");
            adminloginUI(pHead1);
            adminLoginMenu(pHead1);
            break;
        }
        case 2:
        {
            system("clear");
            userloginUI(pHead2);
            loginMenu(pHead2);
            break;
        }
        case 0:
        {
            break;
        }
    }
    return 0;
}

int main(void)
{
    mainMenu();
    return 0;
}