#include "head.h"

int pos = 0;			
word_t **p = NULL;
//sdfsadfdsaf
void main_view(void)		
{
	printf("\n**********************快译通英汉查询系统********************\n\n");
	printf("\t1.载入至内存,提供汉字反查(-text)\n");
	printf("\t2.保存为二进制文件(只写入原库)(-bs)\n");
	printf("\t3.载入二进制文件(-bf)\n");
	printf("\t4.添加用户词库(-add)\n");
	printf("\t5.修改用户词库(-modify)\n");
	printf("\t6.用户词库测试系统(-test)\n");
	printf("\t7.释放内存,文件中查找(-free)\n");
//	printf("\t8.辅助查找,需载入内存(-help)\n");
	printf("\n*************************0.退出*****************************\n");
}

int main(int argc, char *argv[])
{
	char choice[25];
	int i = 0;

	if (argv[1]) {
		strcpy(choice, argv[1]);
		goto check;
	}

	system("clear");
	main_view();
	puts("--------------------正在文件中查找--------------------");

	while (1) {
		printf("输入内容或选择('-v'显示菜单):");
		scanf("%24s", choice);
		getch();
check:
		if (! strcasecmp(choice, "-v") || ! strcasecmp(choice, "-view"))
			main_view();

		else if (! strcasecmp(choice, "0") || ! strcasecmp(choice, "-exit") || ! strcasecmp(choice, "-x"))
			break;

		else if (! strcasecmp(choice, "1") || ! strcasecmp(choice, "-text"))
			load_text_check();

		else if (! strcasecmp(choice, "-bs") || ! strcasecmp(choice, "2"))
			write_binary_check();

		else if (! strcasecmp(choice, "-bf") || ! strcasecmp(choice, "3"))
			load_binary_check();

		else if (! strcasecmp(choice, "-add") || ! strcasecmp(choice, "4"))
			add_word();

		else if (! strcasecmp(choice, "-modify") || ! strcasecmp(choice, "5"))
			modify_word();

		else if (! strcasecmp(choice, "-test") || ! strcasecmp(choice, "6"))
			test();

		else if (! strcasecmp(choice, "-free") || ! strcasecmp(choice, "7")) {
			if (p || user) {
				printf("正在释放......");
				fflush(stdout);
				destroy_p();
				destroy_user();
				puts("完成!");
				puts("--------------------正在文件中查找--------------------");
			}
			else
				puts("~~~~~~未载入内存,无需释放!~~~~~~");
		}

		else {
			i = find(choice);	
			if (i < 0)
				puts("~~~~~~未找到,提示: 选择\"4\"或参数\"-add\"添加自定义单词!~~~~~~");
		}
	}

	if (p || user) {
		printf("释放内存......");
		fflush(stdout);
		destroy_p();
		destroy_user();
		puts("完成!");
	}

	printf("\n谢谢使用!!!\n\n");

	return 0;
}

void print_trans(int n)
{
	int i = 0;

	for (i = 0; i < p[n]->n; i++) 
		printf("\tTrans->%d: %s\n", i + 1, p[n]->trans[i]);
	puts("");
}

void print_trans_user(int n)
{
	int i = 0;

	for (i = 0; i < user[n]->n; i++) 
		printf("\tTrans->%d: %s\n", i + 1, user[n]->trans[i]);
	puts("");
}

void print_key(int n, int count)
{
	printf("\tKey->%d: %s\n", count, p[n]->key);
}

void destroy_p(void)
{
	int i = 0, j = 0;
	
	if (p) {
		for (i = 0; i < pos; i++) {
			for (j = 0; j < p[i]->n; j++) 
				free(p[i]->trans[j]);

			free(p[i]->trans);
			free(p[i]->key);
			free(p[i]);
		}

		free(p);
		pos = 0;
		p = NULL;
	}
}

void destroy_user(void)
{
	int i = 0, j = 0;

	if (user) {
		for (i = 0; i < add_pos; i++) {
			for (j = 0; j < user[i]->n; j++) 
				free(user[i]->trans[j]);

			free(user[i]->trans);
			free(user[i]->key);
			free(user[i]);
		}
		free(user);
		add_pos = 0;
		user = NULL;
	}

	return;
}

void getch(void)
{
	char ch;
	while ((ch = getchar()) != '\n') ;
}

void load_text_check(void)
{
	int result1 = 1, result2 = 1;

	if (! p || ! user) {
		printf("数据载入内存中......");
		fflush(stdout);
		if (! p)
			result1 = read_txtfile();	
		if (! user)
			result2 = read_add();

		if (result1 && result2) {
			sort(p, 0, pos - 1);
			sort(user, 0, add_pos - 1);
			puts("完成!");
			puts("--------------------正在内存中查找--------------------");
		}
		else
			puts("~~~~~~载入内存失败!~~~~~~");
	}
	else 
		puts("~~~~~~数据已在内存,无需重复载入!~~~~~~");

	return;
}

void load_binary_check(void)
{
	if (! p) {
		printf("数据载入内存中......");
		fflush(stdout);
		int result = read_binary();
		sort(p, 0, pos - 1);
		if (! user) {
			read_add();
			sort(user, 0, add_pos - 1);
		}
		if (result) {
			printf("完成!\n");
			puts("--------------------正在内存中查找--------------------");
		}
		else
			puts("载入失败!");
	}
	else
		puts("~~~~~~数据已在内存,无需重复载入!~~~~~~");

	return;
}

void write_binary_check(void)
{
	printf("正在处理......");
	fflush(stdout);

	if (! p) {
		int result = read_txtfile();
		if (! result) {
			puts("~~~~~~处理失败,返回!~~~~~~");
			return;
		}
	}

	write_binary();
	destroy_p();
	printf("完成!\n");	

	return;
}
