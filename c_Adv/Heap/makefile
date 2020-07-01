TARGET= heap.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror
OBJS= heap.o heap_test.o 

$(TARGET): $(OBJS) 
	    $(CC) -o $(TARGET) $(OBJS) ../../DS/vector/libDS.a

heap.o: heap.c  heap.h 						               
			   $(CC) $(CFLAGS) -c heap.c            

heap_test.o: heap_test.c heap.h 				      
	            $(CC) $(CFLAGS) -c heap_test.c    

run:
	./$(TARGET)

clean:
	  rm -f $(TARGET) $(OBJS) 
