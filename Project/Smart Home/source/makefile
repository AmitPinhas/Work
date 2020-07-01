CC = g++
CXX = $(CC)

CPPFLAGS += $(addprefix -I,$(INC_DIRS))
CPPFLAGS += -MMD -MP
CFLAGS = -g3 -pedantic -Wall  -Wextra -fpic
CXXFLAGS = $(CPPFLAGS) $(CFLAGS)
CXXFLAGS += -std=c++17
CXXFLAGS += -O0

INC_DIRS = ../include
#INC_DIRS += ../../source
#INC_DIRS += ../../include/interfaces
#INC_DIRS += ../../include/inl

SOURCES = $(wildcard ../source/*.cpp)
OBJECTS  = $(SOURCES:.cpp=.o)

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS) *.so *.d

