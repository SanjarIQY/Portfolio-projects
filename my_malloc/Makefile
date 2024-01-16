CC = gcc 
CFLAGS = -g -Wall -Wextra -Werror

SRC = malloc/c/*.c 

TARGET = my_malloc

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY :
	fclean

fclean : 
	@rm -f $(TARGET) 