#include "tcp_client.hpp"

#include <unistd.h> // close

namespace advcpp
{
TCPClient::TCPClient(size_t a_portNum, const char* a_ip)
: m_socket()
{
    m_socket.Connect(a_portNum, a_ip);
}

TCPClient::~TCPClient()
{
    close(m_socket.MySocket());
}

void TCPClient::Send(void* a_data, size_t a_dataSize)
{
    send(m_socket.MySocket(), a_data, a_dataSize, 0);
}

void TCPClient::Recv(void* a_buffer, size_t a_bufferSize)
{
    recv(m_socket.MySocket(), a_buffer, a_bufferSize, 0);
}
} // namespace advcpp