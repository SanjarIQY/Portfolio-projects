CC = gcc
SOURCES = ./bsq/c/my_string_lib.c my_mouse.c
TARGET = my_mouse
FLAGS = -fsanitize=address

$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) -o $@ $^

.PHONY: fclean check

fclean:
	@rm -r $(TARGET)