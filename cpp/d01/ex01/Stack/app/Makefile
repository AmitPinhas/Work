
CC= g++
CXX = $(CC)
CPPFLAGS = -I../../../include
CFLAGS= -g3 -pedantic -Wall -Werror -Wextra -I../include 
CXXFLAGS = $(CFLAGS) -std=c++03

app: ../stack/stack.cpp 

test : app 
	./app

clean:
	 rm -f *.o app  
	 
.PHONY: clean	 

	 
	 
	 
