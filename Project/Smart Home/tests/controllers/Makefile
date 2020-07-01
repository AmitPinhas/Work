CC = g++

CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))

CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra -pthread 

CXXFLAGS = $(CFLAGS) 

CXXFLAGS += -std=c++17

CXXFLAGS += -O0

# LDFLAGS += 

# LDLIBS += 

INC_DIRS += ../../include

#INC_DIRS += ../../include

#INC_DIRS += ../book_inc

SOURCES  = $(wildcard ../../source/*.cpp)

#SOURCES += 

#SOURCES += 

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = controller_test

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:

	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:

	valgrind --leak-check=full ./$(TARGET)
	
helgrind:

	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)

