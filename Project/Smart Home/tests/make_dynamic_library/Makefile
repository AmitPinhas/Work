CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

LIB_NAME = FireSensorCreator

CFLAGS = -g3 -pedantic -Wall -Wextra -fPIC 
LFLAGS = -Llib -1$(LIB_NAME) -W1, -rpath, \$$ORIGIN/../lib 
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++17 
CXXFLAGS += -O0
LDFLAGS += -pthread
# LDLIBS += 

INC_DIRS += ../../include 
#INC_DIRS += ../../iq/q1 
#INC_DIRS += ../book_inc

SOURCES  = ../../dynamic_library/fire_sensor.cpp
SOURCES += ../../dynamic_library/fire_sensor_creator.cpp
#SOURCES += ../../src/Text_Transform_src/cap_words.cpp

OBJECTS  = $(SOURCES:.cpp=.o)


.PHONY: clean test all val

all:  $(TARGET)

test: $(TARGET) 
	./$(TARGET)  

#datafile: 
#	python3.7 genprimes.py > datafile
	 
$(TARGET): $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS) *.d *.txt

val:
	valgrind --leak-check=full ./$(TARGET)


hell:

	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)			


