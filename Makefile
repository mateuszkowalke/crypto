CC := gcc
CFLAGS := -Wall -g -o0

BIN := bin
SRC := src

SRCS := $(wildcard $(SRC)/*.c)
BINS := $(patsubst $(SRC)/%.c, $(BIN)/%, $(SRCS))

all: $(BINS)

$(BIN)/%: $(SRC)/%.c
	$(CC) ${CFLAGS} $< -o $@ -lm

$(BIN):
	mkdir $@

clear:
	rm -rf $(BIN)/*
