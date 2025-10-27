CC := gcc
# enable warnings and debug symbols
CFLAGS := -Wall -g

all: listdir helloworld

listdir: listdir.c
	cc $(CFLAGS) listdir.c -o listdir

helloworld: helloworld.c
	cc $(CFLAGS) helloworld.c -o helloworld

clean:
	@rm listdir helloworld
