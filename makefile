OBJ_FILES = src/main.o src/graphics.o src/utils.o
TARGET = out

$(TARGET): $(OBJ_FILES)
	gcc -o $(TARGET) $(OBJ_FILES) -Isrc/ -Wall -Ofast -march=native

$(OBJ_FILES): %.o: %.c
	gcc -c $^ -o $@

clean:
	rm -rf src/*.o
	rm -rf *.o
	rm -rf libtransientfoundation.a

build: $(OBJ_FILES)
	ar -rcs build/libtransientfoundation.a $(OBJ_FILES)
	cp src/*.h build/transientfoundation/