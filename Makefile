all: vle.h vle_internal.h
	gcc -o vle.o vle.c 

test: vle.h vle_internal.h
	gcc -o test test.c vle.c 