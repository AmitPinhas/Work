# makefile sample

TARGET= DLList.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror
OBJS= DLList.o DLListTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) 
           
DLList.o: DLList.c DLList.h list_itr.h
	$(CC) $(CFLAGS) -c DLList.c     

DLListTest.o: DLListTest.c DLList.h list_itr.h
	$(CC) $(CFLAGS) -c DLListTest.c           
        
clear:
	rm -f $(TARGET) $(OBJS)        

