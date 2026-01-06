#include "clist.h"
#include <stdlib.h>
#include <stdio.h>

void clist_init(CList *l)
{
	l->head.next = &l->head;
	l->head.prev = &l->head;
}

bool clist_empty(CList *l)
{
	return l->head.next == &l->head;
}

void clist_insert_front(CList *l, int v)
{
	Node *n = malloc(sizeof(Node));
	n->value = v;

	Node *first = l->head.next;

	n->next = first;
	n->prev = &l->head;
	first->prev = n;
	l->head.next = n;
}

void clist_insert_back(CList *l, int v)
{
	Node *n = malloc(sizeof(Node));
	n->value = v;

	Node *last = l->head.prev;

	n->next = &l->head;
	n->prev = last;
	last->next = n;
	l->head.prev = n;
}

bool clist_remove_front(CList *l, int *out)
{
	if (clist_empty(l))
		return false;

	Node *n = l->head.next;

	if (out)
		*out = n->value;

	n->next->prev = &l->head;
	l->head.next = n->next;

	free(n);
	return true;
}

bool clist_remove_back(CList *l, int *out)
{
	if (clist_empty(l))
		return false;

	Node *n = l->head.prev;

	if (out)
		*out = n->value;

	n->prev->next = &l->head;
	l->head.prev = n->prev;

	free(n);
	return true;
}

void clist_print(CList *l)
{
	Node *cur = l->head.next;
	printf("[ ");
	while (cur != &l->head) {
		printf("%d ", cur->value);
		cur = cur->next;
	}
	printf("]\n");
}
