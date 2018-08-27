#include "head.h"

void add_word(void)
{
	FILE *fp;
	word_t *tmp;
	char str[100];

	fp = fopen("add_dict", "a+");
	tmp = malloc(sizeof(word_t));
	tmp->trans = malloc(4);
	tmp->trans[0] = malloc(1024);
	tmp->key = malloc(100);

	if (! user) { 
		read_add();
		sort(user, 0, add_pos - 1);
	}

	printf("\n提示: 输入\"-exit\"或\"-x\"退出且不保存本词条:\n");
	printf("用户库中目前有 %d 词条!\n", add_pos);

	while (1) {
		printf("正在录入词条 %d :\n", add_pos + 1);
input:
		printf("  输入单词:");
		scanf("%99s", str);
		getch();

		if (! strcasecmp(str, "-exit") || ! strcasecmp(str, "-x"))
			break;

		if ((*str > 'z' || *str < 'a') && (*str > 'Z' || *str < 'A')) {
			puts("~~~~~~仅支持自定义英文单词!~~~~~~");
			goto input;
		}
		
		tmp->n = find_inmem(user, str, 0, add_pos - 1);
		if (tmp->n >= 0) {
			print_trans_user(tmp->n);
			puts("~~~~~~自定义库中已有此此条,请重新输入!~~~~~~");
			goto input;
		}

		tmp->n = find(str);
		if (tmp->n >= 0)	{
			printf("~~~~~~警告!!!原库中已有此词条,允许重复(y)?~~~~~~");
			char ch;
			scanf("%c", &ch);
			getch();

			if (ch != 'y' && ch != 'Y')
				goto input;
		}

		strcpy(tmp->key, "#");
		strcat(tmp->key, str);
		tmp->n = 0;
		printf("\n  %s\n", tmp->key);
		int count = 0;
		strcpy(tmp->trans[0], "Trans:");

		while (1) {
			printf("  输入释义 %d (-end结束):", count + 1);
			scanf("%s", str);
			getch();
			if (! strcasecmp(str, "-exit") || ! strcasecmp(str, "-x"))
				goto exit;
			if (! strcasecmp(str, "-end"))
				break;
			if (count)	
				strcat(tmp->trans[0], "@");
			strcat(tmp->trans[0], str);
			count++;
			printf("  %s\n", tmp->trans[0]);
		}

		if (user) 
			insert_user(tmp, add_pos);

		add_write(tmp);
		sort(user, 0, add_pos - 1);
		add_pos++;
		char choice;
		printf("存储完毕,按'y'继续,其它键退出:");
		scanf("%c", &choice);

		if (choice == 'y' || choice == 'Y')
			continue;

		break;
	}	
exit:
	free(tmp->trans[0]);
	free(tmp->trans);
	free(tmp->key);
	free(tmp);

	return;
}

void modify_word(void)
{
	int i = 0;
	char str[1000], choice;

	if (! user) {
		read_add();
		sort(user, 0, add_pos - 1);
	}

	while (1) {
		puts("~~~~~~\"-exit\"或\"-x\"不保存退出, \"-end\"或\"0\"保存退出~~~~~~");
		printf("输入要修改的单词:");	
		scanf("%99s", str);
		getch();
	
		if (! strcasecmp(str, "-exit") || ! strcasecmp(str, "-x")) 
			return;
		

		if (! strcasecmp(str, "-end") || ! strcasecmp(str, "0"))
			break;

		if ((i = find_inmem(user, str, 0, add_pos - 1)) < 0) {
			puts("~~~~~~未找到,重新输入!~~~~~~");
			continue;
		}

		printf("\t     ->d: 删除此词条\n");
		printf("\tKey  ->%d: %s\n", 0, user[i]->key);
		print_trans_user(i);

		while (1) {
			printf("\t选择修改号,其它键返回:");
			scanf("%c", &choice);
			getch();
			
			if (choice == 'd' || choice == 'D') {
				free(user[i]);
				while (i < add_pos - 1) {
					user[i] = user[i + 1];
					i++;
				} 
				add_pos--;
				break;
			}

			else if (choice == '0') {
				printf("\t输入新值:");
				scanf("%s", str);
				getch();
				printf("\t%s------>", user[i]->key);
				fflush(stdout);
				user[i]->key = realloc(user[i]->key, strlen(str) + 1);
				strcpy(user[i]->key, str);
				printf("%s\n", user[i]->key);
			}

			else if (choice > '0' && choice <= user[i]->n + '0') {
				printf("\t输入新值:");
				scanf("%s", str);
				getch();
				int n = choice - '0' - 1;
				printf("\t%s------>", user[i]->trans[n]);
				fflush(stdout);
				user[i]->trans[n] = realloc(user[i]->trans[n], strlen(str) + 1);
				strcpy(user[i]->trans[n], str);
				printf("%s\n", user[i]->trans[n]);
			}

			else break;
		}
	}

	add_rewrite();
	puts("存储完毕!");

	return;
}

