TARGET= q1
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror
OBJS= q1.o 

$(TARGET): $(OBJS) 
	    $(CC) -o $(TARGET) $(OBJS)  

test:
		./$(TARGET)

q1.o: q1.c			               
			   $(CC) $(CFLAGS) -c q1.c            

clean:
			rm -f $(TARGET) $(OBJS) 
