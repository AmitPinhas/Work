
CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++03 
CXXFLAGS += -O0
LDFLAGS += -lpthread -pthread
# LDLIBS += 

INC_DIRS += ../../../../work/include ../../include ../../include/inl ../../../cdr_server/include/

SOURCES  = $(wildcard ../../source/*.cpp)
SOURCES := $(filter-out ../../source/Query_handler.cpp, $(SOURCES))
SOURCES += ../../../cdr_server/source/cdr.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = dataStorage

.PHONY: clean test all val

all:  $(TARGET) $(INC_DIRS)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:
	valgrind --leak-check=full ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)

