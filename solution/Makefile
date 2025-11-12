CFLAGS += -Wall -Werror -pedantic -std=c11 -g

.PHONY: clean

all: listdir

listdir: listdir.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	@rm listdir
