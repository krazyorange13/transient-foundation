compile:
	@ clang -o out src/*.c -I src/ -Wall -fsanitize=address