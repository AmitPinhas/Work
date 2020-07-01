#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <list>
#include "commons.hpp" // UnCopyable
#include "socket.hpp"

namespace advcpp
{
template <typename NewMessage>
class TCPServer : private UnCopyable
{
public:    
    TCPServer(int a_portNum, int a_sizeListenQueue, int a_maxClients, NewMessage a_newMessage);

    ~TCPServer() NOEXCEPT;

    static void SendMessage(Socket* a_socketClient, void* a_msg, int a_sizeMsg);

    void Run();

    template <typename NewMsg>
    friend class ReciveAndSentData;

private:
    static const int MAX_NUM_DESCRIPTOR = 1024;
    static const int FAIL = -1;
    static void closeClients(Socket* a_clientSocket);
    void WaitForActivity();
    void CheckNewClient();
    void AcceptNewClient();
    void EnterNewClient(int a_socketClient);
    void CheckExistsClient();
    static void CloseClientSocket(Socket* a_clientSocket, TCPServer& a_server);

private:
    Socket m_listenSocket;
    int m_clientCount;
    int m_maxClients;
    std::list<Socket*> m_clientSockets;
 		int m_activity;
		fd_set m_masterFds;
		fd_set m_tmpFds;   
    NewMessage m_newMessage;

};

template <typename NewMessage>
class ReciveAndSentData 
{
public:
    ReciveAndSentData(TCPServer<NewMessage>& a_server); 

    bool operator()(Socket *a_clientSocket);

private:
    static const int BUFFER_SIZE = 4096;

private:
    TCPServer<NewMessage>& m_server; 

};
} // namespace advcpp

#include "tcp_server.inl"

#endif // TCP_SERVER_HPP
