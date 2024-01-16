CC := gcc
CFLAGS := -g -Wall -Wextra -Werror #-g3 -fsanitize=address
SRC_DIR := mouse/c/*.c 
TARGET := my_mouse

SRC := $(wildcard $(SRC_DIR)/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	@$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(TARGET)

fclean: clean
	@rm -f $(TARGET)

.PHONY: all clean fclean