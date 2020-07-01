#include <iostream>
//#include "mu_test.h"
#include "stddef.h"
#include <cassert>
//#include "utility.hpp"

//#include "MutexClass.hpp"
//#include "Thread.hpp"
//#include "EnrichedException.hpp"
//#include "Race_Mutex.hpp"

//#include "Server.hpp"
#include "translator.hpp"
#include "protocol_ui.hpp"
#include <string.h>
#include "tcp_server.hpp"
#include "Query_handler.hpp"
#include "process_manager.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

//advcpp::Server<int> myServer(100, 5000, 10, newMsg);


class App
{
public:
int operator()(advcpp::Socket* a_sock, char* a_buffer, size_t a_size);

};

int App::operator()(advcpp::Socket* a_sock, char* a_buffer, size_t )
{
    char* ptr = static_cast<char*>(a_buffer);
    (void)a_sock;
    std::cout << ptr<<'\n';
    char buffer[200];
      buffer[0]=10;
   // buffer[1] = 0;
   // buffer[2] = 5;
   // buffer[3] = 2;
   // buffer[4] = 6;
   // buffer[5] = 7;
   // buffer[6] = 2;
   // buffer[7] = 3;
   // buffer[8] = 4;
   // buffer[9] = 4;
   // buffer[10] = 8;
    //char num[4] ;
    char* ptrSec = buffer;
    char temp[12] = "0526723448";
    strcat(buffer, temp);
    uint num = 50000;
    ptrSec+= 11;
    memcpy(ptrSec, &num, sizeof(num) );

    num = 222222;  
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 333333;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 444444;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 555555;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 666666;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 777777;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 888888;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 999999;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    
    num = 101010101;
    ptrSec +=   sizeof(num);
    memcpy(ptrSec, &num, sizeof(num));
    num = 2;
   // template <typename T>
    advcpp::TCPServer<App>::SendMessage(a_sock, buffer, 200);
    return 1;
}

/*
UNIT(server_run)
    App app; 
    advcpp::TCPServer<App> myServer(2000,1024, 10, app);
    myServer.Run();

END_UNIT

UNIT(query_run)
   // advcpp::HandlerRequest app; 
    //advcpp::TCPServer<advcpp::HandlerRequest> myServer(2000,1024, 10, app);
    //myServer.Run();
    ASSERT_PASS();
END_UNIT

UNIT(process_run)
    //advcpp::HandlerRequest app; 
    advcpp::ProcessManager HeadProcess(2000,1024, 10);
    HeadProcess.Run();


END_UNIT


TEST_SUITE(Server check )
	//TEST(compilation_check_work)
    //TEST(server_run)
    //TEST(query_run)
    TEST(process_run)

END_SUITE
*/


int main(void)
{
    advcpp::ProcessManager HeadProcess(2000,1024, 10);
    HeadProcess.Run();
}