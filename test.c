#include "head.h"

void test(void)
{
	char choice;

	if (! user)	{
		read_add();
		sort(user, 0, add_pos - 1);
	}

	while (1) {
		printf("**************测试系统****************\n\n");
		printf("\t1.选择题测试\n");
		printf("\t2.填空题测试\n\n");
		printf("***************0.退出*****************\n\n");
		printf("请选择:");
		scanf("%c", &choice);
		getch();
		
		if (choice == '1')
			test_choice();

		if (choice == '2')
			test_blank();

		else
			break;
	}

	return;
}

void test_choice(void)
{
	int num = 0, i = 0, j = 0, count = 0, right = 0, *flag, flag2[4] = {0};
	char *answer, ch, **trans;

	flag = malloc(sizeof(int) * add_pos);
	trans = malloc(sizeof(char *) * 4);
	for (i = 0; i < 4; i++)
		trans[i] = malloc(1024);

	for (num = 0; num < add_pos; num++)								//key标致位数组置0
		flag[num] = 0;
	
	srand(time(NULL));
	while (count < add_pos) {
		num = rand() % add_pos;										//判断key是否重复
		if (flag[num])
			continue;
		
		flag[num] = 1;
		printf("第 %d 题:---->%s\n", ++count, user[num]->key);
		strcpy(trans[0], user[num]->trans[0]);						
		
		for (i = 1; i < user[num]->n; i++)
			strcat(trans[0], user[num]->trans[i]);

		answer = trans[0];											//将正确答案赋到flag2[0]上,并设置0下标防止重复
		flag2[0] = num;												
		i = 1;

		while (i < 4) {												//循环再随机提取3个trans
random:
			num = rand() % add_pos;
			j = 0;
			for (j = 0; j < 4; j++) {								//判断是否存在相同trans值
				if (flag2[j] == num)								//trans标致位数组
					goto random;
			}
			flag2[i] = num;											//不相同将数组一个下标置值,防止下次重复
			
			strcpy(trans[i], user[num]->trans[0]);
			for (j = 1; j < user[num]->n; j++)						//所有释义合并
				strcat(trans[i], user[num]->trans[j]);

			i++;
		}
		
		for (i = 0; i < 4; i++)										//trans标致位数组重新置0
			flag2[i] = 0;
		
		i = 0;
		while (i < 4) {
			j = rand() % 4;											//随机输出四个trans值
			if (flag2[j])											
				continue;
			flag2[j] = 1;

			printf("\t%c : %s\n", i + 65, trans[j]);
			if (trans[j] == answer)
				ch = i + 65;
			i++;
		}

		printf("请选择:");
		scanf("%s", trans[0]);

		if (toupper(*trans[0]) == ch) 
			printf("\t----------------------------->正确+1----> %d\n", ++right);
		else
			printf("\t----------------------------->错误,答案是 %c\n", ch);
		
		printf("按\"x\"或\"0\"退出,其它键继续!");
		scanf("%s", trans[0]);

		if (*trans[0] == '0' || *trans[0] == 'x' || *trans[0] == 'X')
			break;
	}

	if (count == add_pos) 
		puts("已到最后一题!");

	float percent;
	percent = (float)right / (float)count;	
	printf("\n~~~~~~共答题:%d, 正确:%d, 正确率:%.2f%%~~~~~~\n\n", count, right, percent * 100);

	free(flag);
	for (i = 0; i < 4; i++)
		free(trans[i]);
	free(trans);

	return;
}

void test_blank(void)
{
	int num = 0, count = 0, right = 0, *flag;
	char str[100];	

	flag = malloc(sizeof(int) * add_pos);
	srand(time(NULL));
	for (num = 0; num < add_pos; num++)
		flag[num] = 0;

	while (count < add_pos) {
		num = rand() % add_pos;

		if (flag[num]) 
			continue;

		flag[num] = 1;
		printf("第 %d 题:\n", ++count);
		print_trans_user(num);
		printf("\t请输入答案:");
		scanf("%s", str);
		getch();

		if (! strcasecmp(str, user[num]->key)) 
			printf("\t----------------------------->正确+1----> %d\n", ++right);
		else
			printf("\t----------------------------->错误,答案是 %s\n", user[num]->key);

		printf("按\"x\"或\"0\"退出,其它键继续!");
		scanf("%s", str);

		if (*str == '0' || *str == 'x' || *str == 'X')
			break;
	}

	if (count == add_pos) 
		puts("已到最后一题!");
	float percent;
	percent = (float)right / (float)count;	
	printf("\n~~~~~~共答题:%d, 正确:%d, 正确率:%.2f%%~~~~~~\n\n", count, right, percent * 100);
	free(flag);

	return;
}
