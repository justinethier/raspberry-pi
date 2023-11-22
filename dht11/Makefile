
all: example

example: example.c
	gcc -o example example.c -lwiringPi -lwiringPiDev

.phony: clean run

run: example
	sudo ./example

clean:
	rm -rf example
