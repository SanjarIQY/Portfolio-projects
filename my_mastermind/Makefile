CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = m.c
TARGET = my_mastermind

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)