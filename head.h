#ifndef _HEAD_H_
#define _HEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

typedef struct data {
	char *key;
	int n;
	char **trans;
}word_t;

extern word_t **user;
extern word_t **p;
extern int pos;
extern int add_pos;
extern int alpha;

int read_txtfile(void);						//文件相关
void write_binary(void);
int read_binary(void);
void add_write(word_t *);
void add_rewrite(void);
int read_add(void);

void add_word(void);
void modify_word(void);

void insert_array(word_t *, int);
void insert_user(word_t *, int);
void list(void);

void test(void);							//测试
void test_choice(void);
void test_blank(void);

int find(char *);
int find_alpha(char *, int, int);
int find_add(char *, int, int);
int find_infile(char *);
int find_inmem(word_t **, char *, int, int);
int find_chs(char *, int ,int);

void sort(word_t **, int, int);
void merge(word_t **, int, int, int);

void destroy_p(void);
void destroy_user(void);
void getch(void);
void main_view(void);
void print_key(int, int);
void print_trans(int);
void print_trans_user(int);

void load_text_check(void);
void load_binary_check(void);
void write_binary_check(void);

#endif
