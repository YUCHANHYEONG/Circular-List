#include "clist_mt.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

enum {
	PRODUCERS = 64,
	CONSUMERS = 64,
	PER_PROD = 200000
};

static CListMT g_list;

static atomic_long produced = 0;
static atomic_long consumed = 0;
static atomic_int producers_done = 0;

static void *producer_fn(void *arg)
{
	long id = (long)arg;
	long base = id * (long)PER_PROD;

	for (long i = 0; i < PER_PROD; i++) {
		long v = base + i + 1;
		clist_mt_insert_front(&g_list, v);
		atomic_fetch_add_explicit(&produced, 1, memory_order_relaxed);
	}

	atomic_fetch_add_explicit(&producers_done, 1, memory_order_release);
	return NULL;
}

static void *consumer_fn(void *arg)
{
	(void)arg;
	long target = (long)PRODUCERS * (long)PER_PROD;

	for (;;) {
		long cur = atomic_load_explicit(&consumed, memory_order_relaxed);
		if (cur >= target)
			break;

		long v;
		if (clist_mt_remove_back(&g_list, &v)) {
			atomic_fetch_add_explicit(&consumed, 1, memory_order_relaxed);
			continue;
		}

		int done = atomic_load_explicit(&producers_done, memory_order_acquire);
		if (done == PRODUCERS) {
			long c = atomic_load_explicit(&consumed, memory_order_relaxed);
			if (c >= target)
				break;
		}
	}

	return NULL;
}

int main(void)
{
	clist_mt_init(&g_list);

	pthread_t pt[PRODUCERS];
	pthread_t ct[CONSUMERS];

	for (long i = 0; i < CONSUMERS; i++)
		pthread_create(&ct[i], NULL, consumer_fn, (void *)i);

	for (long i = 0; i < PRODUCERS; i++)
		pthread_create(&pt[i], NULL, producer_fn, (void *)i);

	for (int i = 0; i < PRODUCERS; i++)
		pthread_join(pt[i], NULL);

	for (int i = 0; i < CONSUMERS; i++)
		pthread_join(ct[i], NULL);

	printf("produced=%ld, consumed = %ld\n",
			atomic_load_explicit(&produced, memory_order_relaxed),
			atomic_load_explicit(&consumed, memory_order_relaxed));

	clist_mt_destroy(&g_list);
	return 0;
}
