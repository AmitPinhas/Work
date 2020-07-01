
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../include
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra -I../inc 
CXXFLAGS = $(CFLAGS) -std=c++03 -O0

TARGET = rational_test

$(TARGET): ../inc/rational.hpp 

test : $(TARGET)
	./$(TARGET) -v

clean:
	 rm -f *.o $(TARGET) 
	 
.PHONY: clean test	 

	 
	 
	 
