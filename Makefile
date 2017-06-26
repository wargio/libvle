all: vle.h vle_internal.h
	gcc -o test test.c vle.c 