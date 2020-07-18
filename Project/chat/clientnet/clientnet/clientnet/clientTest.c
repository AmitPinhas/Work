#include <stdio.h> /* printf */
#include "../include/clientnet.h"

#define BUFF_SIZE		255
#define SERVER_PORT 	5555
#define SERVER_IP       "127.0.0.1"
#define MSG             "hello there"

int main ()
{
    Client* newClient = NULL;
    char msg [BUFF_SIZE];

    newClient = ClientCreate(SERVER_IP, SERVER_PORT);

	ClientSendMsg(newClient, MSG, sizeof(MSG));
    ClientRecieveMessage(newClient, msg, BUFF_SIZE);
    printf("%s", msg);
		
	return 0;
}