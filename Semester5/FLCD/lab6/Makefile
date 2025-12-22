# Makefile for building the parser with Flex, Bison, and gcc
# On Windows, install WinFlexBison and ensure flex, bison, and gcc are in PATH.

PROJECT = flcd_parser
SRC_DIR = src
INC_DIR = include

LEX_SRC = $(SRC_DIR)/scanner.l
YACC_SRC = $(SRC_DIR)/parser.y
LEX_C   = $(SRC_DIR)/lex.yy.c
YACC_C  = $(SRC_DIR)/parser.tab.c
YACC_H  = $(SRC_DIR)/parser.tab.h
C_SRCS  = $(SRC_DIR)/main.c $(SRC_DIR)/productions.c
OBJS    = $(LEX_C:.c=.o) $(YACC_C:.c=.o) $(C_SRCS:.c=.o)
CFLAGS  = -I$(INC_DIR) -I$(SRC_DIR) -O2 -Wall -Wextra
LDFLAGS = 

all: $(PROJECT)

$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)

$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $(LEX_C) $(LEX_SRC)

$(SRC_DIR)/lex.yy.o: $(LEX_C) $(YACC_H)
	gcc $(CFLAGS) -c $(LEX_C) -o $(SRC_DIR)/lex.yy.o

$(SRC_DIR)/parser.tab.o: $(YACC_C) $(INC_DIR)/productions.h
	gcc $(CFLAGS) -c $(YACC_C) -o $(SRC_DIR)/parser.tab.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/productions.h $(YACC_H)
	gcc $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/productions.o: $(SRC_DIR)/productions.c $(INC_DIR)/productions.h
	gcc $(CFLAGS) -c $(SRC_DIR)/productions.c -o $(SRC_DIR)/productions.o

$(PROJECT): $(LEX_C) $(YACC_C) $(SRC_DIR)/lex.yy.o $(SRC_DIR)/parser.tab.o $(SRC_DIR)/main.o $(SRC_DIR)/productions.o
	gcc $(CFLAGS) $(SRC_DIR)/lex.yy.o $(SRC_DIR)/parser.tab.o $(SRC_DIR)/main.o $(SRC_DIR)/productions.o -o $(PROJECT)

clean:
	rm -f $(PROJECT) $(SRC_DIR)/*.o $(LEX_C) $(YACC_C) $(YACC_H) productions.txt

.PHONY: all clean

