#!/bin/sh

# 1. Program a shell script, which reads two numbers as command line arguments. The
# script should check whether the numbers are identical, and print out the result of
# the check.
#echo "1. identical"
if [ $1 -eq $2 ]; then
    echo "$1 and $2 are identical"
else
    echo "$1 and $2 are not identical"

    # 2. Extend the shell script in a way that if the numbers are not identical, it is checked,
    # which one of the two numbers is the larger one. The result of the check should be
    # printed out.
    #echo "2. larger"
    if [ $1 -gt $2 ]; then
        echo "$1 > $2"
    else
        echo "$1 < $2"
    fi
fi
