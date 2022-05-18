COMPILER=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

SRC=$(wildcard *.c)

vpm: $(SRC)
	$(COMPILER) $(CFLAGS) -o vpm $(SRC)
