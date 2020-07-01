#include "mu_test.h"

#include <iostream>
#include <cstdlib>

#include "protocol_handler_ui.hpp"

static const size_t SIZE = 100;

UNIT(protocol_handler_decoding_test_request_client)
	char* buffer = new char[SIZE];
	uchar type = advcpp::ONE_CLIENT_REQ;
	uchar len = 9;
	uchar ismn[] = "123456789";
	memcpy(buffer, reinterpret_cast<const void *>(static_cast<uchar*>(&type)), sizeof(uchar));
	size_t pos = 1;
	memcpy(buffer + pos, reinterpret_cast<const void *>(static_cast<uchar*>(&len)), sizeof(uchar));
	++pos;
	memcpy(buffer + pos, reinterpret_cast<const void *>(ismn), sizeof(uchar) * len);
	advcpp::ProtocolHandlerUI handler(buffer);
	handler.DecodeQuery();
	ASSERT_EQUAL(handler.Request(), advcpp::ONE_CLIENT);
	ASSERT_EQUAL(handler.Name(), "123456789");
	delete[] buffer;
END_UNIT

UNIT(protocol_handler_decoding_test_request_clients)
	char* buffer = new char[SIZE];
	uchar type = advcpp::ALL_CLIENTS_REQ;
	memcpy(buffer, reinterpret_cast<const void *>(static_cast<uchar*>(&type)), sizeof(uchar));
	advcpp::ProtocolHandlerUI handler(buffer);
	handler.DecodeQuery();
	ASSERT_EQUAL(handler.Request(), advcpp::ALL_CLIENTS);
	delete[] buffer;
END_UNIT

UNIT(protocol_handler_decoding_test_request_operator)
	char* buffer = new char[SIZE];
	uchar type = advcpp::ONE_OPERATOR_REQ;
	uchar len = 18;
	uchar ismn[] = "123456789123456789";
	memcpy(buffer, reinterpret_cast<const void *>(static_cast<uchar*>(&type)), sizeof(uchar));
	size_t pos = 1;
	memcpy(buffer + pos, reinterpret_cast<const void *>(static_cast<uchar*>(&len)), sizeof(uchar));
	++pos;
	memcpy(buffer + pos, reinterpret_cast<const void *>(ismn), sizeof(uchar) * len);
	advcpp::ProtocolHandlerUI handler(buffer);
	handler.DecodeQuery();
	ASSERT_EQUAL(handler.Request(), advcpp::ONE_OPERATOR);
	ASSERT_EQUAL(handler.Name(), "123456789123456789");
	delete[] buffer;
END_UNIT

UNIT(protocol_handler_decoding_test_request_operators)
	char* buffer = new char[SIZE];
	uchar type = advcpp::ALL_OPERATORS_REQ;
	memcpy(buffer, reinterpret_cast<const void *>(static_cast<uchar*>(&type)), sizeof(uchar));
	advcpp::ProtocolHandlerUI handler(buffer);
	handler.DecodeQuery();
	ASSERT_EQUAL(handler.Request(), advcpp::ALL_OPERATORS);
	delete[] buffer;
END_UNIT



UNIT(protocol_handler_encoding_test_one_client)
	char* bufferR = new char[SIZE];
	char* bufferW = new char[SIZE];
	advcpp::Client client("68978", 1, 2, 3, 4, 5, 6, 666, 78787, 99999999 , 878787);
	std::vector<advcpp::Client> clVec;
	clVec.push_back(client);
	advcpp::ProtocolHandlerUI handler(bufferR);
	handler.EncodeQuery(clVec, bufferW);
	uchar type;
	memcpy(&type, bufferW, sizeof(uchar));
	ASSERT_EQUAL(type, advcpp::ONE_CLIENT);
	uint download;
	memcpy(&download, bufferW + 40, sizeof(uint));
	ASSERT_EQUAL(download, 99999999);
	memcpy(&download, bufferW + 36, sizeof(uint));
	ASSERT_EQUAL(download, 78787);
	memcpy(&download, bufferW + 32, sizeof(uint));
	ASSERT_EQUAL(download, 666);
	ASSERT_EQUAL(handler.EncodedMsgLen(), 48);
	delete[] bufferR;
	delete[] bufferW;
END_UNIT


UNIT(protocol_handler_encoding_test_one_operator)
	char* bufferR = new char[SIZE];
	char* bufferW = new char[SIZE];
	advcpp::Operator op(40520,"Golan", 111, 222, 333, 444);
	std::vector<advcpp::Operator> opVec;
	opVec.push_back(op);
	advcpp::ProtocolHandlerUI handler(bufferR);
	handler.EncodeQuery(opVec, bufferW);
	ASSERT_EQUAL(handler.EncodedMsgLen(), 28);
	uchar type;
	memcpy(&type, bufferW, sizeof(uchar));
	ASSERT_EQUAL(type, advcpp::ONE_OPERATOR);
	uint download;
	memcpy(&download, bufferW + 24, sizeof(uint));
	ASSERT_EQUAL(download, 444);
	memcpy(&download, bufferW + 20, sizeof(uint));
	ASSERT_EQUAL(download, 333);
	memcpy(&download, bufferW + 16, sizeof(uint));
	ASSERT_EQUAL(download, 222);
	memcpy(&download, bufferW + 12, sizeof(uint));
	ASSERT_EQUAL(download, 111);
	char name[6];
	memcpy(&name, bufferW + 7, sizeof(char)*5);
	ASSERT_EQUAL(name, op.Brand());
	delete[] bufferR;
	delete[] bufferW;
END_UNIT

TEST_SUITE(the protocol handler on fire)
	TEST(protocol_handler_decoding_test_request_client)
	TEST(protocol_handler_decoding_test_request_clients)
	TEST(protocol_handler_decoding_test_request_operator)
	TEST(protocol_handler_decoding_test_request_operators)
	TEST(protocol_handler_encoding_test_one_client)
	TEST(protocol_handler_encoding_test_one_operator)
END_SUITE


