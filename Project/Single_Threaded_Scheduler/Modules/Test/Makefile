TARGET= single_threaded_scheduler_test.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include
OBJS= 
SRCS = ../t_queue/t_queue.c ../task/task.c ../scheduler/scheduler.c ../executor/executor.c ../time_m/time_m.c ../UI/UI.c Test.c 
$(TARGET): $(SRCS)
	 $(CC) $(CFLAGS) -o $(TARGET) $(SRCS) ../libDS/libDS.a

run :
	./$(TARGET)	 
	 
clean:
	 rm -f $(TARGET) $(OBJS)	 

