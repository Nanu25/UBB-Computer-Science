# Makefile for FA to RG transformation lab

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = fa_rg_demo
SOURCES = main.c fa_rg.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
