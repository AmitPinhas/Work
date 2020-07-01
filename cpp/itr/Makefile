
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../include
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra -I../inc -I../inc_test
CXXFLAGS = $(CFLAGS) -std=c++03 -O0

TARGET = itr_test

$(TARGET): ../inc/itr.hpp ../inc_test/itr_test.hpp

test : $(TARGET)
	./$(TARGET) -v

clean:
	 rm -f *.o $(TARGET) 
	 
.PHONY: clean test	 

val:
	valgrind --leak-check=full ./$(TARGET) 
	 
	 
	 
