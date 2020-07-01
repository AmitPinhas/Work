#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include "commons.hpp" // UnCopyable
#include "socket.hpp"

namespace advcpp
{
class TCPClient : private UnCopyable
{
public:    
    TCPClient(size_t a_portNum, const char* a_ip);

    ~TCPClient();

    void Send(void* a_data, size_t a_dataSize);

    void Recv(void* a_buffer, size_t a_bufferSize);

private:
    Socket m_socket;

};
} // namespace advcpp

#endif // TCP_CLIENT_HPP
