#include "head.h"

int read_txtfile(void)
{
	FILE *fp;

	fp = fopen("dict.txt", "r");
	if (! fp) {
		puts("数据库文件不存在!");
		return 0;
	}
	
	word_t *tmp = malloc(sizeof(word_t));
	tmp->key = malloc(100);
	tmp->trans = malloc(4);
	tmp->trans[0] = malloc(1024);

	while ((fgets(tmp->key, 100, fp))) {
		fgets(tmp->trans[0], 1024, fp);
		insert_array(tmp, pos);
		pos++;
	}
	
	free(tmp->trans[0]);
	free(tmp->trans);
	free(tmp->key);
	free(tmp);
	fclose(fp);

	return 1;
}

void write_binary(void)
{
	FILE *fp = fopen("dict_b", "wb");
	int i = 0, j = 0, len = 0;
	
	fwrite(&pos, 4, 1, fp);
	for (i = 0; i < pos; i++) {
		len = strlen(p[i]->key) + 1;
		fwrite(&len, 4, 1, fp);
		fwrite(p[i]->key, len, 1, fp);
		len = p[i]->n;
		fwrite(&len, 4, 1, fp);
		for (j = 0; j < p[i]->n; j++) {
			len = strlen(p[i]->trans[j]) + 1;
			fwrite(&len, 4, 1, fp);
			fwrite(p[i]->trans[j], len, 1, fp);
		}
	}

	fclose(fp);
	
	return;
}

int read_binary(void)
{
	int i = 0, j = 0, len = 0;
	FILE *fp = fopen("dict_b", "rb");

	if (! fp) {
		puts("文件未创建,请先使用\"-bs\"参数或选择\"2\"创建二进制文件!");
		return 0;
	}

	fread(&pos, 4, 1, fp);
	p = malloc(pos * sizeof(word_t *));
	
	for (i = 0; i < pos; i++) {
		p[i] = malloc(sizeof(word_t));
		fread(&len, 4, 1, fp);
		p[i]->key = malloc(len);
		fread(p[i]->key, len, 1, fp);
		fread(&(p[i]->n), 4, 1, fp);
		p[i]->trans = malloc(4 * p[i]->n);

		for (j = 0; j < p[i]->n; j++) {
			fread(&len, 4, 1, fp);
			p[i]->trans[j] = malloc(len);
			fread(p[i]->trans[j], len, 1, fp);
		}
	}

	fclose(fp);
	
	return 1;
}

void add_write(word_t *tmp)
{
	FILE *fp = fopen("add_dict", "a+");
	
	fprintf(fp, "%s\n", tmp->key);
	fprintf(fp, "%s\n", tmp->trans[0]);
	
	fclose(fp);
	
	return;
}

void add_rewrite(void)
{
	FILE *fp = fopen("add_dict", "w");
	char key[100];
	char trans[1024];
	int i = 0, j = 0;
	
	for (i = 0; i < add_pos; i++) {
		strcpy(key, "#");
		strcat(key, user[i]->key);
		fprintf(fp, "%s\n", key);
		strcpy(trans, "Trans:");

		for (j = 0; j < user[i]->n; j++) {
			strcat(trans, user[i]->trans[j]);
			strcat(trans, "@");
		}

		*(trans + strlen(trans) - 1) = '\0';
		fprintf(fp, "%s\n", trans);
	}
	
	fclose(fp);
	return;
}

int read_add(void)
{
	FILE *fp = fopen("add_dict", "r");

	if (! fp) 
		return 0;
	
	word_t *tmp = malloc(sizeof(word_t));
	tmp->key = malloc(100);
	tmp->trans = malloc(4);
	tmp->trans[0] = malloc(1024);

	while ((fgets(tmp->key, 100, fp))) {
		fgets(tmp->trans[0], 1024, fp);
		insert_user(tmp, add_pos);
		add_pos++;
	}

	free(tmp->trans[0]);
	free(tmp->trans);
	free(tmp->key);
	free(tmp);
	fclose(fp);

	return 1;
}
