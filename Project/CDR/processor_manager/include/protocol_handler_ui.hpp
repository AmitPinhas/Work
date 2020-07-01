#ifndef PROTOCOL_HANDLER_UI_HPP
#define PROTOCOL_HANDLER_UI_HPP

#include <cstddef>//size_t
#include <vector>//vector
#include <string>
#include "client.hpp"
#include "operator.hpp"
#include "protocol_ui.hpp"

namespace advcpp
{

class ProtocolHandlerUI
{
public:
    //a_buffer of server
    ProtocolHandlerUI(char* a_buffer);
    //~ProtocolHandlerUI();
    void DecodeQuery();
    void EncodeQuery(std::vector<Client> const& a_clients, char* a_buffer);
    void EncodeQuery(std::vector<Operator> const& a_operators, char* a_buffer);
    void EncodeQueryClientNotFound(char* a_buffer);
    void EncodeQueryOperatorNotFound(char* a_buffer);

    size_t EncodedMsgLen() const;
    Query Request() const;
    std::string const & Name() const;
private:
    void copyName(uchar a_lenName, size_t a_pos);
private:
    static const size_t NAME_LEN = 64;
    char* m_buffer;
    size_t m_msgLen;
    std::string m_bufferName;
    Query m_req;
};

}//namespace advcpp

#endif //PROTOCOL_HANDLER_UI_HPP