
TARGET= chat.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -Werror -I../include -I../../include -I../server_net/include
OBJS= 
DPATH= -L.
DLIB= -lDS  
SRCS = app.c ../User/User.c ../server_net/server_net.c ../ServerManager/ServerManager.c ../Protocol/protocol.c ../IpHandler/IpHandler.c ../Group/Group.c ../queue/queue.c ../log/log.c
$(TARGET): $(SRCS)
	 $(CC) $(DPATH) $(CFLAGS) -o $(TARGET) $(SRCS) $(DLIB)  
clean:
	 rm -f $(TARGET) $(OBJS)	 

test: $(TARGET)
	./$(TARGET)
	 
	 
	 
