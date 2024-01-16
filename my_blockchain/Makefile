CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRC = source/c/*.c block.c

TARGET = my_blockchain

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY :
	fclean

fclean : 
	@rm -f $(TARGET) 