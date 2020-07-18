#include <stdlib.h> /* size_t */
#include "../include/clientManager.h"


int main(int argc, char const *argv[])
{
    ClientManager* newManager;
    
    newManager = ClientManagerCreate(argv[1], atoi(argv[2]));
    if(NULL == newManager)
    {
        return 0;
    }
    ClientManagerRun(newManager);
    ClientManagerDestroy(&newManager);
    return 0;
}
