
CC = g++
CXX = $(CC)
CPPFLAGS = -I../../include -I../inc -I../inc_test
CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) -std=c++03 -O3

TARGET = shape_test

$(TARGET): ../inc/shape.hpp ../inc/circle.hpp ../src/circle.cpp ../src/shape.cpp ../inc_test/shape_test.hpp ../inc/rectangle.hpp ../src/rectangle.cpp ../inc/point.hpp ../src/point.cpp ../inc/square.hpp ../src/square.cpp ../inc/line.hpp ../src/line.cpp ../inc/horizontal_line.hpp ../src/horizontal_line.cpp ../inc/vertical_line.hpp ../src/vertical_line.cpp

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

