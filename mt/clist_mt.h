#ifndef CLIST_MT_H
#define CLIST_MT_H

#include <stdbool.h>
#include <pthread.h>

typedef struct Node {
	int value;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node head;
	pthread_mutex_t lock;
} CListMT;

void clist_mt_init(CListMT *l);
void clist_mt_destroy(CListMT *l);

void clist_mt_insert_front(CListMT *l, long v);
bool clist_mt_remove_back(CListMT *l, long *out);

#endif
