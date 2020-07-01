#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h> // inet_addr
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>  // inet_addr
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>  // inet_addr
#include <unistd.h> //close (file descriptor)
#include <string>
#include <sys/types.h>  //connect        /* See NOTES */

#define LOOP_BACK_IP "127.0.0.1"

#include "Common.hpp"

static const size_t MAX_IP_LENGTH = 15;

namespace advcpp
{

struct ClientData
{
    struct sockaddr_in sin;
};



template <typename App>    
class Client: private Uncopyable
{
public:
    Client(size_t a_port, char a_ip[MAX_IP_LENGTH] = LOOP_BACK_IP , size_t a_buffer = 4096);
    ~Client();
    void SendMSG(char* str);

private:
    void initClient(); 
    void reciveMSG();

private:
    size_t m_port;
    const size_t m_buffer;
    int m_sock;
    char* m_ip;
    ClientData m_clientData;
    App m_app;

};



}

#include "Client.inl"

#endif /*end client*/
