CC = gcc
CFLAGS = -g -O2 -Wall -Wundef
LDLIBS = -lm

.PHONY: clean datasets

all: dataset-generator

dataset-generator: dataset_generator.c common.h
	$(CC) $(CFLAGS) $< -o $@.elf $(LDLIBS)

datasets:
	./dataset-generator.elf

clean:
	rm -rf dataset-generator.elf

