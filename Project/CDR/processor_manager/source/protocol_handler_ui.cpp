#include "protocol_handler_ui.hpp"
#include <cstring> // memcpy
#include <algorithm> //for_each
#include <cassert> //assert
#include "iostream"

namespace advcpp
{

static bool IsDone(bool a_isDone);
static bool PickTypeDecode(ReqQuery a_req, Query& a_response);
inline static bool IsDone(bool a_isDone);
inline static bool IsNameInRange(uchar a_len);
static void TransferDataToBuffer(size_t& a_pos, char* a_buffer, uint a_currData);
static void TransferNameToBuffer(std::string const &a_currData, size_t& a_pos, char* a_buffer);
static void TransferIdentifierToBuffer(size_t& a_pos, char* a_buffer, Client const& a_cell);
static void TransferIdentifierToBuffer(size_t& a_pos, char* a_buffer, Operator const& a_cell);
static void TransferIdentifierToBuffer(size_t& a_pos, char* a_buffer, Operator const& a_cell);


struct EncodeClient
{
    EncodeClient(char* a_buffer, size_t& a_msgLen)
    : pos(a_msgLen)
    , buffer(a_buffer)
    {
       pos = 2;
    }

    void operator()(Client const& a_cell)
    {
        TransferIdentifierToBuffer(pos, buffer, a_cell);
        TransferDataToBuffer(pos, buffer, a_cell.MinutesIn());
        TransferDataToBuffer(pos, buffer, a_cell.MinutesOut());
        TransferDataToBuffer(pos, buffer, a_cell.MinutesInOutside());
        TransferDataToBuffer(pos, buffer, a_cell.MinutesOutOutside());
        TransferDataToBuffer(pos, buffer, a_cell.SmsIn());
        TransferDataToBuffer(pos, buffer, a_cell.SmsOut());
        TransferDataToBuffer(pos, buffer, a_cell.SmsInOutside());
        TransferDataToBuffer(pos, buffer, a_cell.SmsOutOutside());
        TransferDataToBuffer(pos, buffer, a_cell.Download());
        TransferDataToBuffer(pos, buffer, a_cell.Upload());
    }

    size_t& pos;
    char*  buffer;
};


struct EncodeOperator
{
    EncodeOperator(char* a_buffer, size_t& a_msgLen)
    : pos(a_msgLen)
    , buffer(a_buffer)
    {
       pos = 2;
    }

    void operator()(Operator const& a_cell)
    {
        TransferDataToBuffer(pos, buffer, a_cell.MccMnc());
        TransferIdentifierToBuffer(pos, buffer, a_cell);
        TransferDataToBuffer(pos, buffer, a_cell.MinutesIn());
        TransferDataToBuffer(pos, buffer, a_cell.MinutesOut());
        TransferDataToBuffer(pos, buffer, a_cell.SmsIn());
        TransferDataToBuffer(pos, buffer, a_cell.SmsOut());
    }

    size_t& pos;
    char*  buffer;
};


ProtocolHandlerUI::ProtocolHandlerUI(char* a_buffer)
: m_buffer(a_buffer)
, m_msgLen()
, m_bufferName()
{
    assert(a_buffer != 0);
}

size_t ProtocolHandlerUI::EncodedMsgLen() const
{
    return m_msgLen;
}

Query ProtocolHandlerUI::Request() const
{
    return m_req;
}

std::string const& ProtocolHandlerUI::Name() const
{
    return m_bufferName;
}

void ProtocolHandlerUI::DecodeQuery()
{
   	uchar type;
    memcpy(&type, m_buffer, sizeof(uchar));
    if(IsDone(PickTypeDecode(static_cast<ReqQuery>(type), m_req)))
    {
        return;
    }
    const size_t pos = 1;
    uchar lenName;
    memcpy(&lenName, m_buffer + pos, sizeof(uchar));
    if(IsNameInRange(lenName))
    {
        m_req = QUERY_ERR;
        return;
    }
    copyName(lenName, pos + 1);

}

void ProtocolHandlerUI::EncodeQuery(std::vector<Client> const& a_clients, char* a_buffer)
{
    uchar data = a_clients.size() > 1 ? ALL_CLIENTS:ONE_CLIENT;
    memcpy(a_buffer, &data, sizeof(uchar));
    data = a_clients.size();
    memcpy(a_buffer + 1, &data, sizeof(uchar));
    for_each(a_clients.begin(), a_clients.end(), EncodeClient(a_buffer, m_msgLen));
}


void ProtocolHandlerUI::EncodeQuery(std::vector<Operator> const& a_operators, char* a_buffer)
{
    uchar data = a_operators.size() > 1 ? ALL_OPERATORS:ONE_OPERATOR;
    memcpy(a_buffer, &data, sizeof(uchar));
    data = a_operators.size();
    memcpy(a_buffer + 1, &data, sizeof(uchar));
    for_each(a_operators.begin(), a_operators.end(), EncodeOperator(a_buffer, m_msgLen));
}

void ProtocolHandlerUI::EncodeQueryClientNotFound(char* a_buffer)
{
    uchar data = CLIENT_NOT_FOUND;
    memcpy(a_buffer, reinterpret_cast<const void *>(&data), sizeof(uchar));
}

void ProtocolHandlerUI::EncodeQueryOperatorNotFound(char* a_buffer)
{
    uchar data = OPERATOR_NOT_FOUND;
    memcpy(a_buffer, reinterpret_cast<const void *>(&data), sizeof(uchar));
}

static void TransferDataToBuffer(size_t& a_pos, char* a_buffer, uint a_currData)
{
    memcpy(a_buffer + a_pos, &a_currData, sizeof(uint));
    a_pos += sizeof(uint);
}

static void TransferNameToBuffer(std::string const &a_currData, size_t& a_pos,char* a_buffer)
{
    uchar len = a_currData.size();
    memcpy(a_buffer + a_pos, &len, sizeof(uchar));
    ++a_pos;
    memcpy(a_buffer + a_pos, a_currData.c_str(), sizeof(uchar) * len);
    a_pos += len;
}

static void TransferIdentifierToBuffer(size_t& a_pos, char* a_buffer, Client const& a_cell)
{
    TransferNameToBuffer(a_cell.Imsi(), a_pos, a_buffer);
}

static void TransferIdentifierToBuffer(size_t& a_pos, char* a_buffer, Operator const& a_cell)
{
    TransferNameToBuffer(a_cell.Brand(), a_pos, a_buffer);
}


static bool PickTypeDecode(ReqQuery a_req, Query& a_response)
{
    switch(a_req)
    {
        case ONE_CLIENT_REQ:
                        a_response = ONE_CLIENT;
                        return false;
        case ALL_CLIENTS_REQ:
                        a_response = ALL_CLIENTS;
                        return true;
        case ONE_OPERATOR_REQ:
                        a_response = ONE_OPERATOR;
                        return false;
        case ALL_OPERATORS_REQ:
                        a_response = ALL_OPERATORS;
                        return true;
        default:
                        a_response = QUERY_ERR;
                        return true;
    }
}

inline static bool IsDone(bool a_isDone)
{
    return a_isDone;
}

inline static bool IsNameInRange(uchar a_len)
{
    return a_len > 64 || a_len == 0;
}

void ProtocolHandlerUI::copyName(uchar a_lenName,size_t a_pos)
{
    m_bufferName.clear();
    char bufferName[NAME_LEN];
    memcpy(&bufferName, m_buffer + a_pos, sizeof(uchar) * a_lenName);
    bufferName[a_lenName] = '\0';
    m_bufferName.append(bufferName, a_lenName);
}




} //namespace advcpp

