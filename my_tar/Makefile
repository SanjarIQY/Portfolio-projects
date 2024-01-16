TARGET = my_tar
SRC = tar.c
FLAG = -Wall -Wextra -Werror


$(TARGET) : $(SRC) 
	@gcc -o $@ $< $(FLAG)

run : 
	@./my_tar -cf create test.c

.PHONY : fclean

fclean : 
	@rm -rf $(TARGET)

