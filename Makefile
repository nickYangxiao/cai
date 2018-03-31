all:LottManage

OBJS:= list.o public.o interfaceUI.o admin.o user.o
LOTTMANAGE_OBJS:=LottManage.o $(OBJS)

LottManage:$(LOTTMANAGE_OBJS)
	gcc $(LOTTMANAGE_OBJS) -o LottManage -Wall


%.o:%.c
	gcc -c $< -o $@ -Wall

clean:
	rm -frv LottManage
	rm -frv $(LOTTMANAGE_OBJS)

