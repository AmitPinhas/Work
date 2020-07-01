
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../../../../../include
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra -I../include -I../../Stack/include 
CXXFLAGS = $(CFLAGS) -std=c++03 -O3

TARGET = app

$(TARGET): ../queue/queue.cpp  ../../Stack/stack/stack.cpp ../include/queue.hpp

test : $(TARGET)
	./$(TARGET) -v

clean:
	 rm -f *.o $(TARGET) 
	 
.PHONY: clean test	 

	 
	 
	 
