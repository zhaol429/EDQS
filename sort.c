#include "head.h"

void merge(word_t **p, int start, int mid, int end)
{
	int len1 = mid - start + 1;
	int len2 = end - mid;
	word_t **left = malloc(4 * len1);
	word_t **right = malloc(4 * len2);

	if (! left || ! right) {
		puts("Memory Error!");
		exit(EXIT_FAILURE);
	}

	int i = 0, j = 0, k = 0;

	for (i = 0; i < len1; i++)
		left[i] = p[start + i];
	for (j = 0; j < len2; j++)
		right[j] = p[j + mid + 1];

	i = j = 0;
	k = start;

	while (i < len1 && j < len2) {
		if (strcasecmp(left[i]->key, right[j]->key) < 0)
			p[k++] = left[i++];
		else
			p[k++] = right[j++];
	}

	while (i < len1)
		p[k++] = left[i++];

	while (j < len2)
		p[k++] = right[j++];


	free(left);
	free(right);
}

void sort(word_t **p, int start, int end)
{
	int mid = (start + end) / 2;
	if (start >= end)
		return;

	sort(p, start, mid);
	sort(p, mid + 1, end);
	merge(p, start, mid, end);

	return;
}
