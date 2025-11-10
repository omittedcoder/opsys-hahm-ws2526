CC := gcc
# enable warnings and debug symbols
CFLAGS += -Wall -Werror -pedantic -std=c11 -g

# with this a file named clean can still be used
.PHONY: clean

all: listdir helloworld

listdir: listdir.c
	$(CC) $(CFLAGS) $? -o $@

helloworld: helloworld.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	@rm listdir helloworld
