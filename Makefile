all: libvle.a
	@echo "libvle.a built!"

libvle.a: vle.o
	ar rcs libvle.a vle.o

vle.o: vle.h vle_internal.h
	gcc -c -o vle.o vle.c

test-chain: libvle.a
	gcc -o test test.c libvle.a

clean:
	rm -rf *.o test *.a