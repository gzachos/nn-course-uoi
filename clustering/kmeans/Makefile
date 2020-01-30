CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
LDLIBS = -lm

.PHONY: clean

all: kmeans 

kmeans: kmeans.c ../common.h conf.h
	$(CC) $(CFLAGS) $< -o $@.elf $(LDLIBS)

clean:
	rm -rf kmeans.elf

