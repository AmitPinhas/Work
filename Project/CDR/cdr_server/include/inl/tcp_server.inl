#include <algorithm>  // std::for_each, std::find_if
#include <unistd.h>   // close
#include <sys/time.h> //select 
#include <string.h>   // memset
#include <netinet/in.h>
#include <signal.h> 

namespace advcpp
{
template <typename NewMessage>
TCPServer<NewMessage>::TCPServer(int a_portNum, 
                                 int a_sizeListenQueue, 
                                 int a_maxClients, 
                                 NewMessage a_newMessage)
: m_listenSocket()
, m_clientCount()
, m_maxClients(a_maxClients) 
, m_clientSockets()
, m_activity()
, m_masterFds()
, m_tmpFds()
, m_newMessage(a_newMessage)                              
{
    m_listenSocket.Setsockopt();
    m_listenSocket.Bind(a_portNum);
    m_listenSocket.Listen(a_sizeListenQueue);
    m_listenSocket.NonBlock();

    FD_ZERO(&m_masterFds);
    FD_ZERO(&m_tmpFds);

    FD_SET(m_listenSocket.MySocket(), &m_masterFds);
    
    signal(SIGPIPE, SIG_IGN);    
} 

template <typename NewMessage>
TCPServer<NewMessage>::~TCPServer() NOEXCEPT
{
    close(m_listenSocket.MySocket());
    
    std::list<Socket*>::iterator begin = m_clientSockets.begin();
    std::list<Socket*>::iterator end = m_clientSockets.end();

    std::for_each(begin, end, closeClients);
}

template <typename NewMessage>
void TCPServer<NewMessage>::closeClients(Socket* a_clientSocket)
{
    close(a_clientSocket->MySocket());
    delete a_clientSocket;
}

template <typename NewMessage>
void TCPServer<NewMessage>::SendMessage(Socket* a_socketClient, 
                                        void* a_msg, 
                                        int a_sizeMsg)
{
  a_socketClient->Send(a_msg, a_sizeMsg);  
}   

template <typename NewMessage>
void TCPServer<NewMessage>::Run()
{
    while(true)
    {
        WaitForActivity();
        CheckNewClient();
        CheckExistsClient();
    }
}

template <typename NewMessage>
void TCPServer<NewMessage>::WaitForActivity()
{
    m_tmpFds = m_masterFds;
    m_activity = select(MAX_NUM_DESCRIPTOR, &m_tmpFds, 0, 0, 0);
}

template <typename NewMessage>
void TCPServer<NewMessage>::CheckNewClient()
{
	if(FD_ISSET(m_listenSocket.MySocket(), &m_tmpFds))
	{
		--m_activity;	
		AcceptNewClient();	
	}    
}

template <typename NewMessage>
void TCPServer<NewMessage>::AcceptNewClient()
{
    struct sockaddr_in client_sin ;
	socklen_t addr_len = sizeof(client_sin) ;
	int socketClient = 1 ;    

	while ( socketClient != FAIL )
	{
		socketClient = accept(m_listenSocket.MySocket(), (struct sockaddr *) &client_sin, &addr_len);					   
		if ( socketClient > 0 )
		{	
			EnterNewClient(socketClient);   
		}
	}	    
}

template <typename NewMessage>
void TCPServer<NewMessage>::EnterNewClient(int a_socketClient)
{
    if(m_clientCount >= m_maxClients)
    {
        close(a_socketClient);
        return;
    }

    size_t socketNum = static_cast<size_t>(a_socketClient);
    Socket *client = new Socket(socketNum);

    m_clientSockets.push_back(client);
    FD_SET(client->MySocket(), &m_masterFds);
    ++m_clientCount;
}

template <typename NewMessage>
void TCPServer<NewMessage>::CheckExistsClient()
{
    std::list<Socket*>::iterator begin = m_clientSockets.begin();
    std::list<Socket*>::iterator end = m_clientSockets.end();
    std::list<Socket*>::iterator iter;

    while(m_activity > 0)
    {
        iter = std::find_if(begin, end, ReciveAndSentData<NewMessage>(*this));
        if(m_activity > 0)
        {
            --m_activity;
            begin = m_clientSockets.erase(iter);
        }
    }
}

template <typename NewMessage>
void TCPServer<NewMessage>::CloseClientSocket(Socket* a_clientSocket, TCPServer& a_server)
{
    int clientSocket = a_clientSocket->MySocket();

    FD_CLR(clientSocket, &(a_server.m_masterFds));
    close(clientSocket);
    --(a_server.m_clientCount);
}

template <typename NewMessage>
ReciveAndSentData<NewMessage>::ReciveAndSentData(TCPServer<NewMessage>& a_server)
: m_server(a_server)
{
}

template <typename NewMessage>
bool ReciveAndSentData<NewMessage>::operator()(Socket *a_clientSocket)
{
    int clientSocket = a_clientSocket->MySocket();

    if(FD_ISSET(clientSocket, &(m_server.m_tmpFds)))
    {
        char buffer[BUFFER_SIZE] ;
        size_t sizeBuffer = sizeof(buffer);
        memset( buffer, 0, sizeBuffer);
        int readBytes = recv(clientSocket, buffer, sizeBuffer, 0);
        if(0 == readBytes)
        {
            TCPServer<NewMessage>::CloseClientSocket(a_clientSocket, m_server);
            return true;
        }
        else
        {
            size_t sizeBuffer = sizeof(buffer);

            m_server.m_newMessage(a_clientSocket, buffer, sizeBuffer);
        }

        --(m_server.m_activity);
    }

    if(0 == m_server.m_activity)
    {
        return true;
    }    

    return false;
}
} // namespace advcpp
