BIN=main
# all of the *.c files in this directory, and corresponding .o and .d file names
CFILES=$(wildcard *.c)
COBJS=$(patsubst %.c,%.o,$(CFILES))
DEPS=$(patsubst %.c,%.d,$(CFILES))
CC=gcc # The C Compiler (CC) is gcc
CFLAGS=-O2 -g -Wall -Wextra -Werror -I. -Wno-unused-parameter -MP -MD
LD=gcc # gcc knows how to link too!
LDFLAGS=-L. -g

all: $(BIN)

$(BIN): $(COBJS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) $(COBJS) $(DEPS)

-include $(DEPS)

.PHONY: clean all
