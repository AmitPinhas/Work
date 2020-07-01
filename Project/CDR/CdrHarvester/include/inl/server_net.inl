

namespace advcpp
{


inline ServerNetExeption::ServerNetExeption(const char* a_msg, InfoExeption a_info) NO_EXEPTION
: MyExeption(a_msg, a_info)
{
}

template <typename MsgHendler>
ServerNet<MsgHendler>::ServerNet(MsgHendler a_hendler, size_t a_bufferSize, size_t a_port, size_t a_queueLen)
: m_port(a_port)
, m_hendler(a_hendler)
, m_buffer(new char[a_bufferSize])
{
	int optval = 1;
	struct sockaddr_in sin;

	m_clientNum = 0;

	m_mainSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_mainSock < 3)
	{
		XTHROW(ServerNetExeption, "socket error");
	}
	
	if (setsockopt(m_mainSock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
	{
		XTHROW(ServerNetExeption, "socketOpt error");
	}
	
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(m_port);

	m_sin = sin;
	if (bind(m_mainSock, (struct sockaddr*) &sin, sizeof(sin)) < 0)
	{
		XTHROW(ServerNetExeption, "bind error");
	} 

	if (listen(m_mainSock, a_queueLen) < 0)
	{
		XTHROW(ServerNetExeption, "listen error");
	}
	FD_ZERO(&m_mainFds);
    FD_SET(m_mainSock, &m_mainFds);
}


template <typename MsgHendler>
ServerNet<MsgHendler>::~ServerNet()
{
    delete[] m_buffer;
}

template <typename MsgHendler>
void ServerNet<MsgHendler>::ansClient(int a_clientNum)
{
	int bytes;

	bytes = recv(a_clientNum, m_buffer, sizeof(m_buffer), 0);
	if (bytes <= 0)
	{
		XTHROW(ServerNetExeption, "rcv error");
	}

    m_hendler(m_buffer, a_clientNum);
}

template <typename MsgHendler>
void ServerNet<MsgHendler>::SendMsg(size_t a_clientNum, char* m_msg, size_t a_msgLen)
{
	int bytes = send(a_clientNum, m_msg, a_msgLen, 0);
	if (bytes < 0)
	{
		XTHROW(ServerNetExeption, "send error");
	}
}

template <typename MsgHendler>
void ServerNet<MsgHendler>::weitForCall(fd_set& a_activeClients)
{
	a_activeClients = m_mainFds;
	
	select(MaxSocks, &a_activeClients, NULL, NULL, NULL);
}


template <typename MsgHendler>
void ServerNet<MsgHendler>::newClient()
{
	int newSock = 0;
	int addrLen = sizeof(m_sin);

	/* full no entry */
	if (m_clientNum >= MaxClients)
	{
		newSock = accept(m_mainSock, (struct sockaddr*) &m_sin, (socklen_t*)&addrLen);/// remove casts

		if (newSock < 0)				
		{
            return;
		}
		close(newSock);
		return;
	}

	/* new client */
	newSock = accept(m_mainSock, (struct sockaddr*) &(m_sin), (socklen_t*)&addrLen); //remove casts
	if (newSock < 0)
	{
		XTHROW(ServerNetExeption, "accept error");
	}
	
	FD_SET(newSock, &(m_mainFds) );
	++m_clientNum;
}



template <typename MsgHendler>
void ServerNet<MsgHendler>::answerClients(fd_set& a_activeClients)
{

	if (FD_ISSET(m_mainSock, &a_activeClients))
	{
		try
		{
			newClient();
		}
		catch(...)
		{
		}
		FD_CLR(m_mainSock, &a_activeClients);
	}

	for (size_t i = 3; i < MaxSocks; ++i)
	{
		if (FD_ISSET(i, &a_activeClients))
		{
            try
            {
			    ansClient(i);
            }
            catch(...)
            {
                FD_CLR(i, &m_mainFds);
				m_clientNum--;
            }
		}
	}
}

template <typename MsgHendler>
void ServerNet<MsgHendler>::Run() NO_EXEPTION
{
    fd_set activeClients;
    while(true)
    {
        weitForCall(activeClients);
        answerClients(activeClients);
    }
}


}//namespace advcpp