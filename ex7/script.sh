#!/bin/sh

# 1.1
gcc -g -c file1.c file2.c

# 1.2
gcc -Wl,--start-group file1.o file2.o -Wl,--end-group -g -o file

# 1.3
size file
ldd file
nm file

gcc --static -Wl,--start-group file1.o file2.o -Wl,--end-group -g -o file

size file
ldd file
nm file

# 1.4
#gdb -tui file

