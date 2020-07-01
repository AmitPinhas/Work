# makefile server net and client

TARGET1 = CLIENT
TARGET2 = SERVER

CC = gcc
CFLAGS = -g -ansi -pedantic -Wall -Werror  -I./include 

SERVER = server_net.c server_net_main.c  ./DLList/DLList.c ./DLList/list_functions.c
CLIENT = client.c 


$(TARGET1): $(CLIENT)
	$(CC) $(CFLAGS) -o $(TARGET1) $(CLIENT)

$(TARGET2): $(SERVER)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SERVER)

all: SERVER CLIENT 

clean:
	rm -f $(TARGET) $(OBJS)

