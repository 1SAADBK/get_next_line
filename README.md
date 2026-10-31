*This project has been created as part of the 42 curriculum by sbenkass.*

# Get_next_line

## Description

This project involves implementing a function that takes the file descriptor (fd) of an open file in the system and reads from it until it finds a new line character ‘\n’. It then returns a pointer that points to a string in the heap segment of memory containing that line.
Also, we use a static string to store the remaining text after the new line character, and the read syscall both remember their last state when we called the function the last time. Therefore, during program execution, we don’t get the same line each time.

## Instructions

To use/test this function yourself, you can use it with a test.txt file that contains text with several lines, and also copy this main to a main.c file:
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *str;
	while ((str = get_next_line(fd)))
	{
		printf("%s",str);
		free(str);
		str = NULL;
	}
	close (fd);
}
```

lastly you can compile the code using the shell command

```bash
cc get_next_line.c get_next_line_utils.c main.c -o test
```

# Managing diffrente file descriptors

If you want to get the next line from diffrent file descriptors at once
you can use the bonus function which is prototyped in the get_next_line_bonus.h header file

To use/test this function yourself, you can use it with a test.txt file that contains text with several lines, and also copy this main to a main.c file:
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *str;
	char *str2;
	int i;
	i = 1;
	while ((str = get_next_line(fd)))
	{
		printf("Line %i from test.txt -> %s", i, str);
		free(str);
		str = NULL;
		i++;
	}
	i = 1;
	printf("\n");
	while ((str2 = get_next_line(fd2)))
	{
		printf("Line %i from test2.txt -> %s", i, str2);
		free(str2);
		str2 = NULL;
		i++;
	}
	close (fd);
	close (fd2);
}
```

lastly you can compile the code using the shell command

```bash
cc get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o test
```

## Resources

To implement your own get_next_line function
firstly you gotta learn how static variables work and what a (fd)

### static variable :

is a variable in the function that remembres it’s value from the last call during the program execution, and it is stored in the (.bss) uninitialised variables segment of the memory. After we give it its first value, it then goes to the (.data) initialised variables segment of the memory.

### File descriptors (fd) :

is an integer that refers to an open file in the system, a file that at least has a process that is using it, and we use it a lot when working with system calls like (write, read, open, etc).

### How AI was used while making this C function :

I used AI to help me debug some of the function bugs, also in tracking the reasons of some segfaults in the earlier stages of the development, and in understanding how the system works with file descriptors as well as kernel and syscalls.

## The algorithm

My get_next_line uses 3 main variables to do the job:

### the static stash:

used to store the read bytes from the open file, and also after finishing the job, it stores the remaining characters after the new line ‘\n’.

### the buffer:

used with the syscall read(), to read from the file a BUFFER_SIZE number of bytes, after that we append those bytes to the stash until we find a new line character.

### the line:

After finding the new line character (or end of file, which is the null terminator ‘\0’) in the stash, we copy all the characters to the line except those after the new line or the null terminator (EOF).

### cleaning and preparing for the next call:

After copying to the line that is the one we will return, we then prepare the stash for the next call by leaving only the characters that appear after the new line in it.
also we free the buffer and point it to null, so that we don’t get a leak or a dangling pointer.