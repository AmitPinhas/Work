
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../../../../../include
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra -I../include 
CXXFLAGS = $(CFLAGS) -std=c++03 -O3

TARGET = app

$(TARGET): ../stack/stack.cpp ../include/stack.hpp ../include/exception_stack.hpp ../stack/exception_stack.cpp

test : $(TARGET)
	./$(TARGET)

clean:
	 rm -f *.o $(TARGET) 
	 
.PHONY: clean test	 

	 
	 
	 
