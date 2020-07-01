
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../include -I../inc -I../inc_test
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra 
CXXFLAGS = $(CFLAGS) -std=c++03 -O3 

TARGET = sorted_sequence_test

$(TARGET): ../inc/sorted_sequence.hpp ../inc/cat.hpp ../inc/my_iter.hpp ../inc_test/sorted_sequence_test.hpp ../inc/pred.hpp ../inc/my_iter_rev.hpp

test : $(TARGET)
	./$(TARGET) -v

clean:
	 rm -f *.o $(TARGET) 
	 
.PHONY: clean test	 

valfull:
	valgrind --leak-check=full ./$(TARGET) 

val:
	valgrind ./$(TARGET) 

gdb:
	gdb ./$(TARGET) 	
	 
	 
	 
