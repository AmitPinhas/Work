CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++03 
CXXFLAGS += -O0
# LDFLAGS += 
# LDLIBS += 

INC_DIRS += ../../../include ../inc ../inc_test
#INC_DIRS += ../../include/Text_Transform_inc 
#INC_DIRS += ../book_inc

SOURCES  = $(wildcard ../src/*.cpp)
#SOURCES += $(wildcard ../../src/*.cpp)
#SOURCES += ../../src/Text_Transform_src/cap_words.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

#TARGET = books_test
TARGET = app

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:
	valgrind --leak-check=full ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)			

