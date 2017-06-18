#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "menu_gen.h"

#define DESC "Menu generator"

DEC_MENU(main);
DEC_MENU(1);
DEC_MENU(1_1);
DEC_MENU(2);

#define ngetc(c) (read (0, (c), 1))

int key_parser(int key, int cnts)
{	

	if(key == 'x' || key == 'X') /* Go to up menu */
		return cnts;
	if('a' <= key && key <= 'f') /* Select menu counts > 9*/
		return key - 'a' + 10;
	if('1' <= key && key <= '9') { /* Select menu counts <= 9*/
		int i = key - '0';
		//printf("%d\n",i);
	    if(i <= cnts && i)
			return i;
	}
	return -1;
}

int get_menu_key(int menu_cnt)
{

	char key;
	int k = 0;
	int ret = 0;
	for(;;)	{
        fflush(stdout);
	    k = ngetc(&key);
		if(k == 1) {
			//printf("\nngetc 0x%x\n",key);
			ret = key_parser(key, menu_cnt);
			//printf("key:%d\n",ret);
			if(ret != -1) {
				return ret;
			}
		}
	}
}

static void func1_1()
{
    printf("%s\n",__func__);
}

static void func1()
{
    printf("%s\n",__func__);
}

static void func2()
{
    printf("%s\n",__func__);
}

static void func2_1()
{
    printf("%s\n",__func__);
}

static void menu_exit(menu_ctrl *pmc)
{
    printf("%s\n",__func__);
    pmc->exit = 1;
}

static void sel_menu(menu_ctrl *pmc)
{
	
	if (pmc->sel_menu)
		pmc->sel_menu(pmc);
	else {
		pmc->exit = 1;
	}
}

int main(void)
{
    menu_ctrl *pmc;
    if((pmc = malloc(sizeof(menu_ctrl))) == NULL) return -1;
        
    pmc->exit = 0;
    pmc->sel_menu = MENU(main);
	do {
		sel_menu(pmc);
	} while(!pmc->exit);
	    
}


static struct menu menu_1_1[] =
{
    MENU_FUNC("func1_1",	func1_1),
    MENU_CTRL("Go to up menu",	MENU(main)),
};

static struct menu menu_1[] =
{
    MENU_CTRL("MENU1_1",	MENU(1_1)),
    MENU_CTRL("Go to up menu",	MENU(main)),
};

static struct menu menu_2[] =
{
    MENU_FUNC("func2_1", func2_1),
    MENU_CTRL("Go to up menu",	MENU(main)),
};

static struct menu menu_main[] =
{
	MENU_CTRL("MENU 1",	MENU(1)),
	MENU_CTRL("MENU 2",	MENU(2)),
	MENU_FUNC("func1",	func1),
	MENU_FUNC("func2",	func2),	
	MENU_CTRL("Exit", menu_exit),
};

MENU_TEMP(main, DESC);
MENU_TEMP(1, DESC);
MENU_TEMP(2, DESC);
MENU_TEMP(1_1, DESC);
