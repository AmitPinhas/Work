#include "sender.h"
#include <stdlib.h> /* atoi */

int main(int argc, char const *argv[])
{
    ChatSender* newSender = ChatSenderCreate(atoi(argv[1]), argv[2], argv[3], atoi(argv[4]));
    
    ChatSenderRun(newSender);
    return 0;
}
