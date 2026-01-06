#ifndef CLIST_H
#define CLIST_H

#include <stdbool.h>

typedef struct Node {
	int value;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node head;
} CList;

void clist_init(CList *l);
bool clist_empty(CList *l);

void clist_insert_front(CList *l, int v);
void clist_insert_back(CList *l, int v);

bool clist_remove_front(CList *l, int *out);
bool clist_remove_back(CList *l, int *out);

void clist_print(CList *l);

#endif
