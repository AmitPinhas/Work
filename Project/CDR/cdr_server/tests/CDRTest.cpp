#include "mu_test.h"

#include <iostream> // std::cout
#include <string.h> // strcpy
#include "input_manager.hpp"
#include "cdr.hpp"
#include "protocol_reader.hpp"

typedef void (*NewMessage)(advcpp::Socket*, char*, size_t);

void NewMsg(advcpp::Socket* a_socket, char* a_buffer, size_t )
{
	std::cout << a_buffer << '\n';
	
	char msg[] = "thank you";
	
	advcpp::TCPServer<NewMessage>::SendMessage(a_socket, msg, sizeof(msg));
}

UNIT(tcp_server)
	advcpp::TCPServer<NewMessage> server(5050, 1024, 1024, NewMsg);
	
	server.Run();

END_UNIT

UNIT(server)

    advcpp::InputManager<advcpp::Cdr*> inputManager(1000);

	int portNum = 5050;
	size_t numThreads = 1;
    inputManager.Run(numThreads, portNum, 1000);

END_UNIT

UNIT(pack_unpack)
    advcpp::Cdr firstCdr;
    advcpp::Types type = advcpp::CALL;

    firstCdr.m_type = type;
    strcpy(firstCdr.m_imsi, "123456789123456");    
    strcpy(firstCdr.m_msisdn, "asdfghjklzxcvbn");
    strcpy(firstCdr.m_imei, "lqlqlqlqlqlqlql");
    strcpy(firstCdr.m_mccMnc, "123456");
    strcpy(firstCdr.m_date, "10/10/2000");    
    strcpy(firstCdr.m_time, "12345678");
    strcpy(firstCdr.m_duration, "1313");
    strcpy(firstCdr.m_msisdnDes, "a8a8a8a8a8a8a88");
    strcpy(firstCdr.m_mccMncDes, "987654");   
    firstCdr.m_length = 3;
    strcpy(firstCdr.m_operatorName, "abc"); 

    char buffer[4000];

    advcpp::ProtocolReader::ProtocolPackCall(buffer, &firstCdr);

    advcpp::Cdr secondCdr;  

    advcpp::ProtocolReader::ProtocolUnpackCall(&secondCdr, buffer);  


    std::cout << secondCdr;
    std::cout << (int)secondCdr.m_type << " " <<  secondCdr.m_imsi << " " << secondCdr.m_msisdn << " " << secondCdr.m_imei << " " << secondCdr.m_mccMnc << " " ;              
    std::cout << secondCdr.m_date << " " <<  secondCdr.m_time << " " << secondCdr.m_duration << " " << secondCdr.m_msisdnDes << " " << secondCdr.m_mccMncDes << " " ; 
    std::cout << (int)secondCdr.m_length << " " << secondCdr.m_operatorName << '\n';
    ASSERT_PASS();

END_UNIT

TEST_SUITE(test the cdr on fire)

	TEST(tcp_server)
    //TEST(server)
    IGNORE_TEST(pack_unpack)

END_SUITE
