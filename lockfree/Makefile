CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -pthread

TARGET = test_mpmc
SRCS = clist_mt.c test_mpmc.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c clist.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
