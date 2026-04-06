CFLAGS = -g -Wall -ansi -pedantic -std=c89
CTARGETS = main.c ../dstring.c

all: static
	
static:
	gcc $(CFLAGS) $(CTARGETS) -o task3
run:
	./task3 in.txt out.txt lex 
	cat out.txt
