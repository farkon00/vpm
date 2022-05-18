COMPILER=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -ggdb

SRC=$(wildcard *.c)

vpm: $(SRC)
	$(COMPILER) $(CFLAGS) -o vpm $(SRC)
