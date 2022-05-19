COMPILER=gcc
CFLAGS=-Wall -Wswitch -Werror -Wextra -fsanitize=address -std=c11 -pedantic -ggdb

SRC=$(wildcard src/*.c)

vpm: $(SRC)
	$(COMPILER) $(CFLAGS) -o vpm $(SRC)
