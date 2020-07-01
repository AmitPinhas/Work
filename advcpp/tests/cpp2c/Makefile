CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP

CFLAGS = -g3 -pedantic  
CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++17 
CXXFLAGS += -O0
LDFLAGS += -pthread
# LDLIBS += 

INC_DIRS += ../../../include ../../include ../../include/inl 
#INC_DIRS += ../../iq/q1 
#INC_DIRS += ../book_inc

SOURCES  = $(wildcard ../../source/*.cpp)
#SOURCES += $(wildcard ../../../cpp/src/utils.cpp)
#SOURCES += ../../src/Text_Transform_src/cap_words.cpp

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET = pointsNew

.PHONY: clean test all val

all:  $(TARGET)


points: points.cpp

pointsNew: CFLAGS += -ansi 
pointsNew: pointsNew.c


fromC.txt: pointsNew
	./pointsNew > fromC.txt

fromCpp.txt: points
	./points > fromCpp.txt

test: fromC.txt fromCpp.txt   
	diff fromC.txt fromCpp.txt   



#datafile: 
#	python3.7 genprimes.py > datafile
	 
$(TARGET): $(OBJECTS)

clean:
<<<<<<< HEAD
	rm -f $(OBJECTS) $(TARGET) $(DEPENDS) *.d *.txt
=======
	rm -f $(OBJECTS) $(DEPENDS) fromC.txt fromCpp.txt *.d  points pointsNew
>>>>>>> 949210163cdd3701cea5d32fb45f1ab214c44a22

val:
	valgrind --leak-check=full ./$(TARGET)


hell:

	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET)


DEPENDS = $(OBJECTS:%.o=%.d)

-include $(DEPENDS)			

