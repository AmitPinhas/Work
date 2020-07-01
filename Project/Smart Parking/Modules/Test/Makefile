TARGET= smart_parking.out
CC= gcc
CFLAGS= -ansi -g -pthread -pedantic -Wall -Werror -I../include 
OBJS= 
SRCS = ../car/car.c ../time_m/time_m.c ../event/event.c  ../MyMalloc/MyMalloc.c ../gate/gate.c ../camera/camera.c ../queue/queue.c ../smart_parking/smart_parking.c ../hash/hash.c  Test.c 
$(TARGET): $(SRCS)
	 $(CC) $(CFLAGS) -o $(TARGET) $(SRCS) 

run :
	./$(TARGET)	 
	 
clean:
	 rm -f $(TARGET) $(OBJS)	 

