CC := gcc
# enable warnings and debug symbols
CFLAGS += -Wall -Werror -pedantic -g

# with this a file named clean can still be used
.PHONY: clean

#all: mytime zombie

# mytime: mytime.c
# 	$(CC) $(CFLAGS) $? -o $@

# zombie: zombie.c
# 	$(CC) $(CFLAGS) $? -o $@

SRC=$(wildcard *.c)
BIN=$(SRC:%.c=%)

all: $(BIN)
	
%: %.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	@rm $(BIN)