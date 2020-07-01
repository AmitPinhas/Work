
CC = g++
CXX = $(CC)
CPPFLAGS = -I../../include -I../inc -I../inc_test
CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) -std=c++03 -O3

TARGET = text_test

$(TARGET): ../inc/actions.hpp ../src/actions.cpp ../inc/i_input_text.hpp ../src/i_input_text.cpp ../inc/readers.hpp ../src/readers.cpp ../inc/i_output_text.hpp ../src/i_output_text.cpp ../inc/writters.hpp ../src/writters.cpp ../inc/transform.hpp ../src/transform.cpp

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

