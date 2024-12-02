OBJ_FILES = src/main.o src/graphics.o src/utils.o
TARGET = out

BUILDDIR = build
BUILD_DIRS = $(shell find build/ -type d)
BUILD_FILES = $(shell find build/ -type f -name "*")

# TODO: check if this is right
ifeq ($(PREFIX),)
	PREFIX = /usr/local
endif

$(TARGET): $(OBJ_FILES)
	gcc -o $(TARGET) $(OBJ_FILES) -Isrc/ -Wall -Ofast -march=native

$(OBJ_FILES): %.o: %.c
	gcc -c $^ -o $@

clean:
	rm -rf src/*.o
	rm -rf *.o
	rm -rf libtransientfoundation.a

build: $(OBJ_FILES)
	mkdir -p $(BUILDDIR)
	ar -rcs $(BUILDDIR)/libtransientfoundation.a $(OBJ_FILES)
	cp src/*.h $(BUILDDIR)/transientfoundation/

install: $(BUILD_DIRS) $(BUILD_FILES)
	mkdir -p $(PREFIX)/include/transientfoundation
	cp build/*.a $(PREFIX)/lib
	cp build/transientfoundation/*.h $(PREFIX)/include/transientfoundation/
