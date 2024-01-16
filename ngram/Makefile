CC = gcc
TARGET = my_ngram
SRC = my_ngram.c
CFLAGS =  -Wall -Wextra -Werror

.PHONY: fclean

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

fclean:
	rm -f $(TARGET)


