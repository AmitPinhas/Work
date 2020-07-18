#include <stdio.h> /* printf */
#include "../include/clientManager.h"
#include "../include/group.h"

static void TestClient()
{
    ClientManager* newManager;
    
    char* _ip = "127.0.0.01";
    int port = 4444;
    newManager = ClientManagerCreate(_ip, port);
    
    TestFunc(newManager);
    return;
}

static void TestGroupManger()
{
    GroupManager* newGroupmanger;
    
    newGroupmanger = GroupManagerCreate();
    
    GroupTestFunc(newGroupmanger);
    return;
}

int main()
{
    TestGroupManger();
    return 0;
}
