namespace advcpp
{

template <typename App>
void Client<App>::initClient()
{
    memset(&m_clientData.sin, 0, sizeof(m_clientData.sin));
    m_clientData.sin.sin_family =AF_INET;
    m_clientData.sin.sin_addr.s_addr = inet_addr( m_ip );
    m_clientData.sin.sin_port=htons( m_port );

    if( int flag = connect( m_sock, (struct sockaddr*)&(m_clientData.sin), sizeof(m_clientData.sin) ) < 0)
    {
        if(flag == EPERM)
            std::cout<<errno<<'\n';

        throw "connection failed";
        memset(&m_clientData.sin, 0, sizeof(m_clientData.sin) );
    }
}

template <typename App>
Client<App>::Client(size_t a_port, char a_ip[15], size_t a_buffer)
:   m_port(a_port)
,   m_buffer(a_buffer)
,   m_ip(new char[ 15 ] )
{
    strcpy(m_ip, a_ip);
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sock<0)
    {
           throw "socket failed";
        
    }
    initClient();
}

template <typename App>
Client<App>::~Client()
{
    delete[] m_ip;
}


template <typename App>
void Client<App>::reciveMSG()
{
    char str[4096];

    int len=sizeof(str), read_bytes;

    read_bytes = recv(m_sock, (void*)str, len, 0);
   
    if(read_bytes==0)
    {
        close(m_sock);
        return;
    }

    else 
    {
        if(read_bytes<0)
        {
            throw "recv failed";
            return; 
        }
    }

    m_app(str);
}


template <typename App>
void Client<App>::SendMSG(char* a_str)
{
    int send_bytes;

    int size = strlen(a_str);

    send_bytes=send( m_sock, (void*)a_str, size, 0 );

    if(send_bytes<0)
    {
        throw "send failed";
        return;
    }

    reciveMSG( );

    return;
}


}
