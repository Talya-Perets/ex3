CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean

all: StrList
	
StrList: Main.o StrList.o
	$(CC) $(CFLAGS) Main.o StrList.o -o StrList

Main.o: Main.c StrList.h
	$(CC) $(CFLAGS) -c Main.c

StrList.o: StrList.c StrList.h
	$(CC) $(CFLAGS) -c StrList.c

clean:
	rm -f *.o StrList
