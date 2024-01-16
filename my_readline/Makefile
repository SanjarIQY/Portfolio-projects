CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = my_readline.c
TARGET = my_readline

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)