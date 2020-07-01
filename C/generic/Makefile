# Main File
TARGET = generic.out

CC = gcc
CFLAGS = -ansi -g -pedantic -Wall -Werror 

# Objects
P_OBJS = generic.o generic_test.o

# Compile & Link
$(TARGET): $(P_OBJS) 
	$(CC) -o $(TARGET) $(P_OBJS) 
	
# Compile	
generic.o: generic.c generic.h 
	$(CC) $(CFLAGS) -c generic.c 

generic_test.o: generic_test.c generic.h 
	$(CC) $(CFLAGS) -c generic_test.c 	
	
run:
	./$(TARGET)

# Clean
clean:
	rm -f $(TARGET) $(P_OBJS) 	
