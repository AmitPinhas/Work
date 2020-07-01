# Main File
TARGET = sorts.out

CC = gcc
CFLAGS = -ansi -g -pedantic

# Libreries
ADTD_DIR = ../ADTDefs/
VECTOR_DIR = ../vector/
STACK_DIR = ../stack/

# Objects
S_OBJS = sorts.o sorts_test.o
V_OBJS = $(VECTOR_DIR)vector.o
STACK_OBJ = $(STACK_DIR)stack.o

# Compile & Link
$(TARGET): $(S_OBJS) $(V_OBJS) $(STACK_OBJ)
	$(CC) -o $(TARGET) $(S_OBJS) $(V_OBJS) $(STACK_OBJ) 
	
# Compile	
sorts.o: sorts.c sorts.h $(ADTD_DIR)ADTDefs.h $(STACK_DIR)stack.h
	$(CC) $(CFLAGS) -c sorts.c 

sorts_test.o: sorts_test.c sorts.h $(ADTD_DIR)ADTDefs.h 
	$(CC) $(CFLAGS) -c sorts_test.c 
	
vector.o: $(VECTOR_DIR)vector.c $(VECTOR_DIR)vector.h $(ADTD_DIR)ADTDefs.h
	$(CC) $(CFLAGS) -c dyVec.c	

stack.o: $(STACK_DIR)stack.c $(STACK_DIR)stack.h $(ADTD_DIR)ADTDefs.h $(VECTOR_DIR)vector.h 
	$(CC) $(CFLAGS) -c stack.c	
	
# Clean
clean:
	rm -f $(TARGET) $(H_OBJS) $(V_OBJS)
	
