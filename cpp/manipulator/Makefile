
CC = g++
CXX = $(CC)
CPPFLAGS = -I../../include -I../inc -I../inc_test
CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) -std=c++03 -O0

TARGET = manipulator_test

$(TARGET): ../inc/manipulator.hpp ../src/manipulator.cpp ../inc/base_manipulator.hpp ../src/base_manipulator.cpp ../inc/other_text.hpp ../inc/base_text.hpp 

test: $(TARGET)
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

