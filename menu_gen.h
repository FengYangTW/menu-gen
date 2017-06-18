#ifndef _menu_gen_h
#define _menu_gen_h
/*
 * MENU template 
 * 
 * Menu generator
 *---------------------------
 *1-MENU 1
 *2-MENU 2
 *3-func1
 *4-func2
 *x-Exit
 *---------------------------
 *
 */
typedef struct menu_ctrl menu_ctrl;
struct menu_ctrl {
	void (*sel_menu)(menu_ctrl *);
	int exit;
};

#define DEC_MENU(name) static void sel_menu_ ## name (menu_ctrl *)

#define MENU(N) sel_menu_ ## N
typedef struct menu menu;

#define MENU_FUNC(DESC, N) { .description = DESC, .func = N, .ctrl = NULL}
#define MENU_CTRL(DESC, N) { .description = DESC, .func = NULL, .ctrl = N}
#define MENU_ENTRY(NAME) {#NAME, NAME ## _main}
/*Factory test menu */
struct menu {
	char *description;	
	void (*func) ();
	void (*ctrl) (menu_ctrl *);
};


/* Factory Test MENU Template */
#define MENU_TEMP(N, T) \
static void sel_menu_ ## N(menu_ctrl *pmc) {  \
	struct menu *p = menu_ ## N;  \
	int menu_cnt = sizeof(menu_ ## N)/sizeof(menu_ ## N[0]); \
	int j = menu_cnt; \
	char i = 1; \
	printf("\n"T"\n"); \
	printf("---------------------------\n"); \
	while(j--) { \
		if (j) \
			if (i >= 10) \
				printf("%c-%s\n", i - 10 + 'a', p->description); \
			else \
				printf("%d-%s\n", i, p->description); \
		else \
			printf("x-%s\n", p->description); \
		p++; \
		i++; \
	} \
	printf("---------------------------\n"); \
	j = get_menu_key(menu_cnt); \
	printf("\n"); \
	if(menu_ ## N[j - 1].func) {\
		pmc->sel_menu = sel_menu_ ## N; \
		menu_ ## N[j - 1].func(); \
	} else \
		pmc->sel_menu = menu_ ## N[j - 1].ctrl; \
}


#endif

