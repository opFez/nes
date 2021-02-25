CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99

all: dump

dump: dump.c
	$(CC) $(CFLAGS) $< -o $@
