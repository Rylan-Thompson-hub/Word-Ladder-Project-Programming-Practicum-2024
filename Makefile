build:
	gcc -g -std=c11 -D_POSIX_C_SOURCE=200809L -Wall main.c -o wordladder

run: build
	./wordladder

clean:
	rm -f wordladder
