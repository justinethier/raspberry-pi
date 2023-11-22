
all: example

example: example.c
	gcc -o example example.c -lwiringPi -lwiringPiDev

.phony: format clean run

format:
	clang-format -i example.c

run: example
	sudo ./example

clean:
	rm -rf example
