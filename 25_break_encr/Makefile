CC = gcc
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all clean

all: breaker

breaker: breaker.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f breaker
