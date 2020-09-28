SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
EXE := $(BIN_DIR)/allocator

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEBUG=-g
FLAGS=-Wall $(DEBUG)

all:
	gcc $(FLAGS) -o $(EXE) $(SRC)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
