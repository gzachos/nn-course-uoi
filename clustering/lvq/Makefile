CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
LDLIBS = -lm

.PHONY: clean

all: lvq 

lvq: lvq.c ../common.h conf.h
	$(CC) $(CFLAGS) $< -o $@.elf $(LDLIBS)

clean:
	rm -rf lvq.elf

