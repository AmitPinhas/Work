#makefile

TARGET= multiApp
TARGET1= senderApp
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include/ -I../../include/
CPPFLAGS += &(addprefix -I,&(INC_DIR))
OBJS=  multi.o multiApp.o msgque.o protocol.o
OBJS1=  sender.o senderApp.o msgque.o protocol.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) 

$(TARGET1): $(OBJS1)
	$(CC) -o $(TARGET1) $(OBJS1) 

multi.o: multi.c multi.h ../../include/chatprotocol.h ../../include/protocol.h
	$(CC) $(CFLAGS) -c multi.c

multiApp.o: multiApp.c multi.h 
	$(CC) $(CFLAGS) -c multiApp.c

sender.o: sender.c sender.h ../../include/chatprotocol.h ../../include/protocol.h
	$(CC) $(CFLAGS) -c sender.c

senderApp.o: senderApp.c sender.h 
	$(CC) $(CFLAGS) -c senderApp.c

protocol.o: ../../protocol/protocol.c ../../include/protocol.h ../../include/chatprotocol.h
	$(CC) $(CFLAGS) -c ../../protocol/protocol.c

msgque.o: ../msgque/msgque.c ../include/msgque.h
	$(CC) $(CFLAGS) -c ../msgque/msgque.c
	
valgrind_full:
	valgrind --leak-check=full ./$(TARGET)

all: multiApp senderApp

clean:
	rm -f $(OBJS) $(OBJS1)
