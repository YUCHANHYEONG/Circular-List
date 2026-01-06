#include "clist.h"
#include <stdio.h>

int main(void)
{
	CList l;
	clist_init(&l);

	clist_insert_front(&l, 2);
	clist_insert_front(&l, 1);
	clist_insert_back(&l, 3);
	clist_insert_back(&l, 4);

	clist_print(&l);

	int x;
	clist_remove_front(&l, &x);
	printf("pop front: %d\n", x);

	clist_remove_back(&l, &x);
	printf("pop back: %d\n", x);

	clist_print(&l);

	return 0;
}
