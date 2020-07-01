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

INC_DIRS += ../include 
INC_DIRS += ../../cdr_server/include 
INC_DIRS += ../../processor_manager/include 
INC_DIRS += ../../cdr_server/include/inl 
INC_DIRS += ../../processor_manager/include/inl 
#INC_DIRS += ../book_inc

SOURCES += $(wildcard ../../processor_manager/source/*.cpp)
SOURCES += $(wildcard ../../cdr_server/source/*.cpp)
SOURCES  += $(ServerRunTest.cpp)
#SOURCES  += ../../cdr_server/source/socket.cpp
#SOURCES  += ../../processor_manager/source/protocol_handler_ui.cpp
#SOURCES  += ../../processor_manager/source/client.cpp
#SOURCES  += ../../processor_manager/source/operator.cpp
#SOURCES += ../../src/Text_Transform_src/cap_words.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = ServerRunTest

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)

val:
	valgrind --leak-check=full ./$(TARGET)

hell:
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)

DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)

