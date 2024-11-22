compile:
	@ gcc -o out src/*.c -I src/ -Wall -Ofast -march=native

lib:
	gcc -c src/graphics.c src/utils.c -Isrc/
	ar -rcs libtransientfoundation.a *.o
	cp libtransientfoundation.a build/libtransientfoundation.a
	rm libtransientfoundation.a
	rm *.o

test:
	gcc -o test.out test.c -L. -ltransientfoundation -Isrc/
