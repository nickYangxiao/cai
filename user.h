#ifndef _USER_H_
#define _USER_H_

#include "./list.h"

userNode *login(userNode *pHead);
int Register(userNode *pHead);
int userDate(char *name);
int buy_lott(char *name);
int buy_record(char  *name);
int add_bal(char *name);
int update_pwd(char *name);
int judge(userNode *pHead);
int userMenu(char *name);
int main(void);

#endif
