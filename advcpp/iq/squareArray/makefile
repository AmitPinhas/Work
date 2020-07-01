TARGET= square
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror
OBJS= squareArrayTest.o 

$(TARGET): $(OBJS) 
	    $(CC) -o $(TARGET) $(OBJS)            

bstree_test.o: squareArrayTest.c 		      
	            $(CC) $(CFLAGS) -c squareArrayTest.c  

test:
		./$(TARGET)

clean:
			rm -f $(TARGET) $(OBJS) 
