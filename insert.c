#include "head.h"

int alpha = 0;
word_t **user = NULL;

void insert_array(word_t *tmp, int pos)
{
	extern word_t **p;
	int count = 0;
	
	if (*(tmp->key + strlen(tmp->key) - 1) == '\n')
		*(tmp->key + strlen(tmp->key) - 1) = '\0';
	if (*(tmp->trans[0] + strlen(tmp->trans[0]) - 1) == '\n')
		*(tmp->trans[0] + strlen(tmp->trans[0]) - 1) = '\0';   	//去掉字符串\n

	p = realloc(p, 4 * (pos + 1));
	p[pos] = malloc(sizeof(word_t));
	p[pos]->key = malloc(strlen(tmp->key) + 1);
	strcpy(p[pos]->key, tmp->key + 1);

	if (tolower(*p[pos]->key) >= 'a' && tolower(*p[pos]->key) <= 'z')
		alpha++;
	char str[1024];
	strcpy(str, tmp->trans[0]);
	char *token = strtok(str, ":");
	p[pos]->trans = NULL;

	while ((token = strtok(NULL, "@"))) {
		p[pos]->trans = realloc(p[pos]->trans, 4 * (count + 1));
		p[pos]->trans[count] = malloc(strlen(token) + 1);
		strcpy(p[pos]->trans[count], token);
		count++;
	}

	p[pos]->n = count;
	return;
}

void insert_user(word_t *tmp, int pos)
{
	int count = 0;

	if (*(tmp->key + strlen(tmp->key) - 1) == '\n')
		*(tmp->key + strlen(tmp->key) - 1) = '\0';
	if (*(tmp->trans[0] + strlen(tmp->trans[0]) - 1) == '\n')
		*(tmp->trans[0] + strlen(tmp->trans[0]) - 1) = '\0';   	//去掉字符串\n

	user = realloc(user, 4 * (pos + 1));
	user[pos] = malloc(sizeof(word_t));
	user[pos]->key = malloc(strlen(tmp->key) + 1);
	strcpy(user[pos]->key, tmp->key + 1);

	char str[1024];
	strcpy(str, tmp->trans[0]);
	char *token = strtok(str, ":");
	user[pos]->trans = NULL;

	while ((token = strtok(NULL, "@"))) {
		user[pos]->trans = realloc(user[pos]->trans, 4 * (count + 1));
		user[pos]->trans[count] = malloc(strlen(token) + 1);
		strcpy(user[pos]->trans[count], token);
		count++;
	}
	
	user[pos]->n = count;
	
	return;
}
