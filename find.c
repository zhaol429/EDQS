#include "head.h"

int add_pos = 0;

int find(char *str)
{
	int i = 0, j = 0;

	if (! p) { 
		i = find_infile(str);
		return i;
	}

	else {
		i = find_inmem(p, str, 0, pos - 1);
		j = find_inmem(user, str, 0, add_pos - 1);

		if (i >= 0 && j >= 0) {
			puts("~~~~~~原库:~~~~~~");
			print_trans(i);
			puts("~~~~~~自定义词库:~~~~~~");
			print_trans_user(j);
		}
		else if (i >= 0)
			print_trans(i);
		else if (j >= 0)
			print_trans_user(j);

		if (*str < 'A') {
			int k = find_chs(str, 0, alpha);

			if (k < 0 && i < 0)
				return -1;
			else 
				return 0;
		}
	}

	return i > j ? i : j;
}

int find_inmem(word_t **tmp, char *str, int start, int end)
{
	int mid = 0;

	while (start <= end) {
		mid = (end + start) / 2;
		
		if (! strcasecmp(tmp[mid]->key, str))
			return mid;
		
		if (strcasecmp(tmp[mid]->key, str) > 0)
			end = mid - 1;
		
		if (strcasecmp(tmp[mid]->key, str) < 0)
			start = mid + 1;
	}

	return mid = -1;
}

int find_chs(char *str, int start, int end)
{
	int i = 0, j = 0, count = 1;

	puts("以下根据汉语释义反查单词,供参考:");
	for (i = start; i < end; i++) 
		for (j = 0; j < p[i]->n; j++) 
			if (strstr(p[i]->trans[j], str)) {
				print_key(i, count);
				count++;
				break;
			}

	if (count == 1) {
		puts("~~~~~~未找到!~~~~~~");;
		i = -1;
	}
	puts("");		

	return i;
}

int find_infile(char *src)
{
	FILE *fp = fopen("dict.txt", "r");
	char *str = malloc(strlen(src) + 3);
	char key1[100], key2[100], trans1[1024], trans2[1024], *p1 = NULL, *p2 = NULL;

	strcpy(str, "#");
	strcat(str, src);
	strcat(str, "\n");

	while ((p1 = fgets(key1, 1024, fp))) {
		if (! strcasecmp(key1, str)) {
			fgets(trans1, 1024, fp);
			break;
		}
		fgets(trans1, 1024, fp);
	}
	fclose(fp);


	fp = fopen("add_dict", "r");
	while ((p2 = fgets(key2, 1024, fp))) {
		if (! strcasecmp(key2, str)) {
			fgets(trans2, 1024, fp);
			break;
		}
		fgets(trans2, 1024, fp);
	}
	fclose(fp);

	free(str);
	if (! p1 && ! p2)
		return -1;

	int count1 = 0, count2 = 0;
	if (p1) { 
		if (p2)
			puts("~~~~~~原库:~~~~~~");
		char *token1 = strtok(trans1, ":");
		while ((token1 = strtok(NULL, "@"))) {
			printf("\tTrans->%d: %s\n", count1 + 1, token1);
			count1++;
		}
		count1 = 1;
	}

	if (p2) {
		if (p1)
			puts("~~~~~~自定义词库:~~~~~~");
		char *token2 = strtok(trans2, ":");
		while ((token2 = strtok(NULL, "@"))) {
			printf("\tTrans->%d: %s\n", count2 + 1, token2);
			count2++;
		}
		count2 = 2;
	}

	return count1 + count2;
}

