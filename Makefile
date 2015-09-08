all: fsub

fsub: fsub.c
	$(CC) -Wall -Wextra -pedantic -std=c11 -O2 -flto -funroll-loops -o $@ $<

install: fsub
	cp fsub /usr/local/bin/fsub
