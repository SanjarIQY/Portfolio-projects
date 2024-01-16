CC = gcc 
CFLAGS = -g3 -Wall -Wextra -Werror #-fsanitize=address

SRC = my_printf.c

TARGET = my_printf

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY :
	fclean

fclean : 
	@rm -f $(TARGET) 