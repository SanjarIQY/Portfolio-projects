# Welcome to My Readline
***

## Task
the task was about to read file and return line by line despite what number of bytes we will give to read function.

## Description
it was really diffuclt for me and took a month(any project didn't take so much time) to see success in terminal. I searched and learned some docs from internet but my mentor really helped me compelet code.

## Installation
it is not a big project, thus there is no need to install it.

## Usage
The function my_readline reads a line from the strean represented by fd and returns it into an allocated string (heap or stack ?). It stops when either the newline character is read or when the end-of-file is reached, whichever comes first. The newline character is not copied to the string.

On success, a pointer to the string is returned. On error, a null pointer is returned. If the end-of-file occurs before any characters have been read, the string remains unchanged.

Number of characters read will be set by the global variable READLINE_READ_SIZE You are allowed to maximum two global variables (one for your "storage" and one for READLINE_READ_SIZE). Be ready, we will change the value of READLINE_READ_SIZE

```
./my_readline Makefile

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = my_readline.c
TARGET = my_readline

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
