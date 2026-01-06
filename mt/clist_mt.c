#include "clist_mt.h"
#include <stdlib.h>

void clist_mt_init(CListMT *l)
{
	l->head.next = &l->head;
	l->head.prev = &l->head;
	pthread_mutex_init(&l->lock, NULL);
}

bool clist_empty_unsafe(CListMT *l)
{
	return l->head.next == &l->head;
}

void clist_mt_destroy(CListMT *l)
{
	pthread_mutex_lock(&l->lock);
	Node *cur = l->head.next;
	while (cur != &l->head) {
		Node *n = cur ;
		cur = cur->next;
		free(n);
	}
	l->head.next = &l->head;
	l->head.prev = &l->head;
	pthread_mutex_unlock(&l->lock);

	pthread_mutex_destroy(&l->lock);
}

void clist_mt_insert_front(CListMT *l, long v)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->value = v;

	pthread_mutex_lock(&l->lock);

	Node *first = l->head.next;

	n->next = first;
	n->prev = &l->head;
	first->prev = n;
	l->head.next = n;

	pthread_mutex_unlock(&l->lock);
}

bool clist_mt_remove_back(CListMT *l, long *out)
{
	pthread_mutex_lock(&l->lock);

	if (clist_empty_unsafe(l)) {
		pthread_mutex_unlock(&l->lock);
		return false;
	}

	Node *n = l->head.prev;

	if (out)
		*out = n->value;

	n->prev->next = &l->head;
	l->head.prev = n->prev;

	pthread_mutex_unlock(&l->lock);

	free(n);
	return true;
}
