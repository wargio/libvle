all: libvle.a
	@echo "libvle.a built!"

libvle.a: vle.o
	ar rcs libvle.a vle.o

vle.o: vle.h vle_internal.h
	gcc -Os -fPIE  -Wall -c -o vle.o vle.c

test-chain: libvle.a
	gcc -Wall -O0 -o test test.c libvle.a

clean:
	rm -rf *.o test *.a