TARGET= bstree.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror
OBJS= bstree.o bstree_test.o

$(TARGET): $(OBJS) 
	    $(CC) -o $(TARGET) $(OBJS)  

bstree.o: bstree.c bstree.h 				               
			   $(CC) $(CFLAGS) -c bstree.c            

bstree_test.o: bstree_test.c bstree.h			      
	            $(CC) $(CFLAGS) -c bstree_test.c   

clean:
			rm -f $(TARGET) $(OBJS) 
