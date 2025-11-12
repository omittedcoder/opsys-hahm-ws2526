#!/bin/sh

# 3. Program a shell script, which reads so long text on the command line, until it is
# terminated by typing END. The script should convert the text, which is read in from
# the command line, to uppercase.
echo "3. read to uppercase"
until [ "${INPUT}" = 'END' ]; do
    TEXT="$TEXT$INPUT\n"
    read INPUT
done
echo "${TEXT}" | tr '[:upper:]' '[:lower:]'
