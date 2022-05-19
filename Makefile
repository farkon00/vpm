COMPILER=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -ggdb

SRC=$(wildcard vpm/*.c)

vpm: $(SRC)
	$(COMPILER) $(CFLAGS) -o vpm $(SRC)
