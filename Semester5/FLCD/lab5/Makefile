# Simple Makefile for building the lexer with Flex and gcc
# On Windows, install WinFlexBison and ensure flex and gcc are in PATH.

PROJECT = flcd_lexer
SRC_DIR = src
INC_DIR = include

LEX_SRC = $(SRC_DIR)/scanner.l
LEX_C   = $(SRC_DIR)/lex.yy.c
C_SRCS  = $(SRC_DIR)/main.c $(SRC_DIR)/st.c $(SRC_DIR)/fa_validate.c
OBJS    = $(LEX_C:.c=.o) $(C_SRCS:.c=.o)
CFLAGS  = -I$(INC_DIR) -O2 -Wall -Wextra
LDFLAGS = 

all: $(PROJECT)

$(LEX_C): $(LEX_SRC)
	flex -o $(LEX_C) $(LEX_SRC)

$(SRC_DIR)/lex.yy.o: $(LEX_C)
	gcc $(CFLAGS) -c $(LEX_C) -o $(SRC_DIR)/lex.yy.o

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/tokens.h $(SRC_DIR)/st.h
	gcc $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/st.o: $(SRC_DIR)/st.c $(SRC_DIR)/st.h
	gcc $(CFLAGS) -c $(SRC_DIR)/st.c -o $(SRC_DIR)/st.o

$(SRC_DIR)/fa_validate.o: $(SRC_DIR)/fa_validate.c $(SRC_DIR)/fa_validate.h
	gcc $(CFLAGS) -c $(SRC_DIR)/fa_validate.c -o $(SRC_DIR)/fa_validate.o

$(PROJECT): $(LEX_C) $(SRC_DIR)/lex.yy.o $(SRC_DIR)/main.o $(SRC_DIR)/st.o $(SRC_DIR)/fa_validate.o
	gcc $(CFLAGS) $(SRC_DIR)/lex.yy.o $(SRC_DIR)/main.o $(SRC_DIR)/st.o $(SRC_DIR)/fa_validate.o -o $(PROJECT)

clean:
	rm -f $(PROJECT) $(SRC_DIR)/*.o $(SRC_DIR)/lex.yy.c pif.txt st.txt lexical_errors.txt

.PHONY: all clean
