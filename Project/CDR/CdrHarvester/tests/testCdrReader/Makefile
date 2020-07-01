CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic -Wall -Werror -Wextra -pthread
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++03 
CXXFLAGS += -O0


INC_DIRS += ../../../include ../../include/ 

SOURCES = $(wildcard ../../source/*.cpp)

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = ReaderTest

.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET)
	rm -Rf testto testfrom	
	mkdir -p testto testfrom
	cp data/litleCdrRecord.cdr testfrom/litleCdrRecord.cdr 
	./$(TARGET) -v
	rm -Rf testto testfrom

$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS)
	rm -Rf testto testfrom

val:
	valgrind --leak-check=full ./$(TARGET)

hall:
	


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)


