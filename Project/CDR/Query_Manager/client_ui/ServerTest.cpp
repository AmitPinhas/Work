 #include <iostream>
#include "mu_test.h"
#include "stddef.h"
#include <cassert>
//#include "utility.hpp"

//#include "MutexClass.hpp"
//#include "Thread.hpp"
//#include "EnrichedException.hpp"
//#include "Race_Mutex.hpp"

#include "Client.hpp"
#include "protocol_ui.hpp"
#include "QueryMenager.hpp"
#include "translator.hpp"


class app
{
public:
    int operator()(char* a_str)
    {
        std::cout<<a_str<<'\n';
        return 1;
    }
};


/*debug use*/
class AppOut
{
public:
    int operator()(char* a_str);

};

inline int AppOut::operator()(char* a_str)
{
    if(a_str[0] == 112)
    {
        advcpp::ResponseQueryClients temp;
        advcpp::Translator::ClientRequestDecode(&temp, a_str);
        std::cout<< static_cast<int>(temp.m_type)<<'\n';
        std::cout << temp.m_clients[0].m_imsi;
        std::cout<<'_'<< temp.m_clients[0].m_totalMinutesIn<< '_'<< temp.m_clients[0].m_totalMinutesOut;
        std::cout<<'_'<< temp.m_clients[0].m_totalMinutesInOutside<< '_'<< temp.m_clients[0].m_totalMinutesOutOutside;
        std::cout<<'_'<< temp.m_clients[0].m_totalSmsIn<< '_'<< temp.m_clients[0].m_totalSmsOut;
        std::cout<<'_'<< temp.m_clients[0].m_totalSmsInOutside<< '_'<< temp.m_clients[0].m_totalSmsOutOutside;
        std::cout<<'_'<< temp.m_clients[0].m_download<< '_'<< temp.m_clients[0].m_upload<<'\n';
    }
    else
    {
        advcpp::ResponseQueryOperators temp;
        advcpp::Translator::OperatorRequestDecode(&temp, a_str);
        std::cout<< static_cast<int>(temp.m_type)<<'\n';
        std::cout<< temp.m_operators[0].m_MccAndMnc<<'_';
         std::cout<<"m_length="<< static_cast<int>(temp.m_operators[0].m_length)<<'_';
        std::cout<< temp.m_operators[0].m_name<<'_';
        std::cout<<'_'<< temp.m_operators[0].m_totalMinutesIn;
        std::cout<<'_'<< temp.m_operators[0].m_totalMinutesOut;
        std::cout<<'_'<< temp.m_operators[0].m_totalSmsIn;
        std::cout<<'_'<< temp.m_operators[0].m_totalSmsOut<<'\n';

    }
    
    return 1;
}

UNIT(compilation_check_work)
		ASSERT_PASS();

END_UNIT


UNIT(client_genery_work)
    char strIP[15] = "127.0.0.1";
    advcpp::Client<app> my_client(2000, strIP);
    int index = 10;
    char str[100] = "loh pidr";
    char probel = ' ';
    char aIndex;
    while(index--)
    {
        aIndex = 'A' + index;
        strcat(str, &probel);
        strcat(str, &aIndex);
        my_client.SendMSG(str);
    }
    my_client.SendMSG(str);
    ASSERT_PASS();
END_UNIT

UNIT(ui_work)
    char strIP[15] = "127.0.0.1";
    advcpp::QueryMenager<AppOut> my_ui(2000, strIP);
    my_ui.Menu();
    ASSERT_PASS();
END_UNIT


TEST_SUITE(Server check )
	TEST(compilation_check_work)
    IGNORE_TEST(client_genery_work)
    TEST(ui_work)
END_SUITE
