CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra -pthread
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++03 
CXXFLAGS += -O0
# LDFLAGS += 
# LDLIBS += 

INC_DIRS += ../../../include ../../include ../../include/inl
INC_DIRS += ../../../cpp/inc 
#INC_DIRS += ../book_inc

SOURCES  = $(wildcard ../../source/*.cpp)
SOURCES += $(wildcard ../../../cpp/src/utils.cpp)
#SOURCES += ../../src/Text_Transform_src/cap_words.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = hashTest

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET) datafile
	./$(TARGET) -v

datafile: 
	python3.7 genprimes.py > datafile
	 
$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:
	valgrind --leak-check=full ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)			

