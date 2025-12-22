CC ?= gcc
CFLAGS += -std=c11 -Wall -Wextra -Iinclude -I../include
LDFLAGS ?=

LL1_SRC := src/main.c src/ll1_parser.c
LL1_OBJ := $(LL1_SRC:.c=.o)
LL1_TARGET := ll1_parser

SEM_SRC := src/seminar_parser.c
SEM_OBJ := $(SEM_SRC:.c=.o)
SEM_TARGET := seminar_parser

.PHONY: all clean

all: $(LL1_TARGET) $(SEM_TARGET)

$(LL1_TARGET): $(LL1_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(SEM_TARGET): $(SEM_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(LL1_OBJ) $(SEM_OBJ) $(LL1_TARGET) $(SEM_TARGET)


