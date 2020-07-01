#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/types.h> 
#include <sys/socket.h>
#include "commons.hpp"
#include "exceptions_definitions.hpp"

namespace advcpp
{
class SocketException : public EnrichedExeption
{
public:
    SocketException(const char* a_error_msg, XtendedInformation const& a_info) THROW2(std::exception, std::ios_base::failure)
    : EnrichedExeption(a_error_msg, a_info)
    {
    }
};

class Socket : private UnCopyable
{
public:    
   Socket(int a_domain = AF_INET, int a_type = SOCK_STREAM, int a_protocol = 0);
   Socket(size_t a_socketNum);

    //~Socket() NOEXCEPT; = default

    void Setsockopt();

    void Bind(int a_portNum);

    void Listen(int a_sizeListenQueue);

    void NonBlock();

    int MySocket();

    void Send(void* a_msg, int a_sizeMsg, int a_flag = 0);

    void Connect(size_t a_portNum, const char* a_ip);

private:
    int m_socket;
};
} // namespace advcpp

#endif // SOCKET_HPP
