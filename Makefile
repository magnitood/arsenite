.PHONY: clean all

all: main

main: main.c
	gcc -Wall -Wextra -ggdb main.c -o main -I./

clean:
	rm -rf main
