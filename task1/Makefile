CFLAGS = -g -Wall -ansi -pedantic -std=c99
CTARGETS = main.c dynarr.c

static: compile

all: compile

compile:
	gcc $(CFLAGS) $(CTARGETS) -o task1

start:
	echo 3 2 1 | ./task1 12

