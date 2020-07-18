#makefile

TARGET= libADD.so
CC= gcc
CFLAGS= -ansi -g  -pedantic -Wall -Werror -I../include/ 
OBJS= add.o

$(TARGET): $(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS) 

add.o: ../aa/add.c ../include/add.h
	$(CC) $(CFLAGS) -c -fpic ../aa/add.c

valgrind_full:
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
