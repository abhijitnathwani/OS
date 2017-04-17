CC=gcc
flags=-lm
echo `$CC -g -o $1 $1.c $flags`
