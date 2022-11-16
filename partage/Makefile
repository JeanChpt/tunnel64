SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

OUT := $(BIN_DIR)/out
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := gcc
CFLAGS := -Wall

.PHONY: all clean

all: $(OUT)

$(OUT): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

veryclean: clean
	@$(RM) -rv $(BIN_DIR)

-include $(OBJ:.o=.d)