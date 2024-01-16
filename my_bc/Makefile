CC = gcc 
CFLAGS = -g -Wall -Wextra -Werror 

SRC = s_source/*.c bc.c

TARGET = my_bc

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY :
	fclean

fclean : 
	@rm -f $(TARGET) 