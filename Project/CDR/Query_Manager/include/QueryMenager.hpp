#ifndef UI_HPP
#define UI_HPP

#include "Client.hpp"
#include "translator.hpp"
#include "protocol_ui.hpp"
#include  <iostream>
#include "Common.hpp"

namespace advcpp
{

static const int MAX_IP_LENGTH = 15;

enum RequestList
{
    CLIENT_REQUEST = 1,
    OPERATOR_REQUEST
};

class Irequest: private Uncopyable
{
public:
    virtual size_t CreateMsg(char* a_buffer) = 0;
};

class RequestClientMSG: public Irequest 
{
public:
    RequestClientMSG(){}
    size_t CreateMsg(char* a_buffer);
};

class RequestOperotorMSG: public Irequest 
{
public:
    RequestOperotorMSG(){}
    size_t CreateMsg(char* a_buffer);
};

template <typename App>
class QueryMenager
{
public:
    QueryMenager(size_t a_port, char a_ip[MAX_IP_LENGTH] = LOOP_BACK_IP , size_t a_buffer = 4096);
    void Menu();

private:
    int displayMenu();

private:
    Client<App> m_queryRequest;

};






}

#include "QueryMenager.inl"

#endif  /*UI.hpp*/


