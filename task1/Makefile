CFLAGS = -g -Wall -ansi -pedantic -std=c99
CTARGETS = main.c ../dynarr.c

static: compile

all: compile

compile:
	gcc $(CTARGETS) $(CFLAGS) -o task1

run:
	echo 3 2 1 | ./task1 12

