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

INC_DIRS += ../../../../work/include
INC_DIRS += ../../include/ ../../../cdr_server/include/

#SOURCES  = $(wildcard ../book_src/*.cpp)
#SOURCES += $(wildcard ../../src/*.cpp)
SOURCES += ../../source/protocol_handler_ui.cpp
SOURCES += ../../../cdr_server/source/cdr.cpp
SOURCES += ../../source/client.cpp
SOURCES += ../../source/operator.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = protocolUI

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

