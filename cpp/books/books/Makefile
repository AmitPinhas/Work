
CC = g++
CXX = $(CC)
CPPFLAGS = -I../../../include -I../inc -I../inc_test
CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) -std=c++03 -O0

TARGET = books_test

$(TARGET): ../inc/IInputData.hpp ../src/IInputData.cpp ../inc/FileReader.hpp ../src/FileReader.cpp ../inc/Book.hpp ../src/Book.cpp ../inc/Library.hpp ../src/Library.cpp ../inc/Parser.hpp ../src/Parser.cpp

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

