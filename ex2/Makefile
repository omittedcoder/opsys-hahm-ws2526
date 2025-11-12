CC := gcc
# enable warnings and debug symbols
CFLAGS += -Wall -Werror -pedantic -std=c11 -g

# with this a file named clean can still be used
.PHONY: clean

all: listdir

listdir: listdir.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	@rm listdir
