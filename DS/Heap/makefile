TARGET= heap.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= heap.o heap_test.o vector.o

$(TARGET): $(OBJS) 
	    $(CC) -o $(TARGET) $(OBJS)  

heap.o: heap.c  ADTDefs.h heap.h 						               
			   $(CC) $(CFLAGS) -c heap.c            

heap_test.o: heap_test.c ADTDefs.h heap.h vector.h 				      
	            $(CC) $(CFLAGS) -c heap_test.c   

vector.o: vector.c ADTDefs.h vector.h vector_test.h			      
	            $(CC) $(CFLAGS) -c vector.c   

clean:
			rm -f $(TARGET) $(OBJS) 
