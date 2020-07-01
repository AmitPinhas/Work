# Main File
TARGET = vector.out

CC = gcc
CFLAGS = -ansi -g -pedantic -Wall -Werror

# Objects
S_OBJS = vector_test.o 

# Compile & Link
$(TARGET): $(S_OBJS) 
	$(CC) -o $(TARGET) $(S_OBJS) libDS.a

vector_test.o: vector_test.c vector.h vector_test.h 
	$(CC) $(CFLAGS) -c vector_test.c 
		

# Clean
clean:
	rm -f $(TARGET) $(S_OBJS) 	
