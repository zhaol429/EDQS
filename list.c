#include "head.h"

void list(void)
{
	extern word_t **p;
	extern int pos;

	int i = 0, j = 0;
	puts("welcome to list!");

	for (i = 0; i < pos; i++) {
		sleep(1);
		printf("p[%d]->key = %s\n", i, p[i]->key);
		printf("p[%d]->n = %d\n", i, p[i]->n);
		for (j = 0; j < p[i]->n; j++)
			printf("p[%d]->trans[%d] = %s\n", i, j, p[i]->trans[j]);
	}

	return;
}
