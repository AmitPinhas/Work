#ifndef CLIENT_NET_HPP
#define CLIENT_NET_HPP

#include <stdio.h>
#include <string.h> 
#include <sys/types.h>      
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <string>

#include "exeption.hpp"
#include "common.hpp"

namespace advcpp
{


class ClientNetExeption : public MyExeption
{
public:
	ClientNetExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};

class client_net : private UnCopyAble
{
public:
    client_net(const char* a_ip, size_t a_port);

    void MsgSend(void* a_buff, int a_size);
    void MsgRecive(void* a_buff, int a_size);

private:
    int m_serverSock;
    sockaddr_in m_sin;
    
};

inline ClientNetExeption::ClientNetExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}

}//namespace advcpp

#endif//CLIENT_NET_HPP