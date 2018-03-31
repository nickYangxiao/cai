#ifndef _ADMIN_H_
#define _ADMIN_H_

#include"./list.h"

int AdminRegister(lottNode *pHead);
int adminlogin(lottNode *pHead);
int addFunc(lottNode *pHead);
int delFunc(lottNode *pHead);
int checkFunc(lottNode *pHead);
void showAllUser(userNode *pHead);
int openFunc(lottNode *pHead);
int adminFunc();

#endif
