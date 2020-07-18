#makefile
TARGET= test
CC= gcc
CFLAGS= -ansi -g -pedantic -I../include/ -I../../include/
INC_DIR=
CPPFLAGS += &(addprefix -I,&(INC_DIR))
DPATH= -L../../lib/
DLIB= -lDS -lrt -pthread
OBJS=  test.o clientManager.o clientnet.o ui.o entrance.o protocol.o group.o msgque.o

$(TARGET): $(OBJS)
	$(CC) $(DPATH) -o $(TARGET) $(OBJS) $(DLIB) 

test.o: test.c ../include/clientManager.h ../include/group.h
	$(CC) $(CFLAGS) -c test.c

clientManager.o: ../clientManager/clientManager.c ../include/clientManager.h ../include/ErrDefs.h ../../include/chatprotocol.h
	$(CC) $(CFLAGS) -c ../clientManager/clientManager.c

clientnet.o: ../clientnet/clientnet.c ../include/clientnet.h ../include/ErrDefs.h
	$(CC) $(CFLAGS) -c ../clientnet/clientnet.c

ui.o: ../ui/ui.c ../include/ui.h ../include/ErrDefs.h
	$(CC) $(CFLAGS) -c ../ui/ui.c

entrance.o: ../entrance/entrance.c ../include/entrance.h ../include/ErrDefs.h ../../include/chatprotocol.h
	$(CC) $(CFLAGS) -c ../entrance/entrance.c

group.o: ../group/group.c ../include/group.h ../include/ErrDefs.h ../../include/protocol.h ../../include/chatprotocol.h
	$(CC) $(CFLAGS) -c ../group/group.c

msgque.o: ../msgque/msgque.c ../include/msgque.h
	$(CC) $(CFLAGS) -c ../msgque/msgque.c

protocol.o: ../../protocol/protocol.c ../../include/protocol.h ../../include/chatprotocol.h
	$(CC) $(CFLAGS) -c ../../protocol/protocol.c

valgrind_full:
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
