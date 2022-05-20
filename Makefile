COMPILER=gcc
CFLAGS=-Wall -Wswitch -Werror -Wextra -std=c11 -pedantic -ggdb

SRC=$(wildcard src/*.c)

vpm: $(SRC)
	$(COMPILER) $(CFLAGS) -o vpm $(SRC)
