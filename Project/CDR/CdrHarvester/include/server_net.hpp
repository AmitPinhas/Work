#ifndef SERVER_NET_HPP
#define SERVER_NET_HPP

#include <stdio.h>		// printf, perror
#include <unistd.h>		// close
#include <string.h>		// memset
#include <arpa/inet.h>	// socket, inet_addr
#include <stdlib.h>		// malloc
#include <fcntl.h>		// fcntl
#include <errno.h>		// errno
#include <sys/types.h> 
#include <sys/time.h>

#include "exeption.hpp"
#include "common.hpp"

namespace advcpp
{

class ServerNetExeption : public MyExeption
{
public:
	ServerNetExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION;
};



template <typename MsgHendler>
class ServerNet : private UnCopyAble
{
public:
    ServerNet(MsgHendler a_hendler, size_t a_bufferSize, size_t a_port , size_t a_queueLen);
    ~ServerNet();

    void Run() NO_EXEPTION;

	static void SendMsg(size_t sockNum, char* m_msg, size_t a_msgLen);

private:
    void weitForCall(fd_set& a_activeClients);
    void answerClients(fd_set& a_activeClients);
    void newClient();
    void ansClient(int a_clientNum);

private:
    int m_mainSock;
	int m_clientNum;
	size_t m_port;
	struct sockaddr_in m_sin;
	fd_set m_mainFds;
    MsgHendler m_hendler;
    fd_set activeClients;
    char* m_buffer;

    static const int MaxSocks = 1024;
    static const int MaxClients = 1000;
};



}//advcpp namespace
#include "inl/server_net.inl"
#endif //SERVER_NET_HPP

