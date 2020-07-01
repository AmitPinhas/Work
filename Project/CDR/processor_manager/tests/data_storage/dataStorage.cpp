#include "mu_test.h"

#include <iostream>
#include <cstring> //strcpy
#include <cstdlib> //atoi
#include "data_storage.hpp"



UNIT(processor_manager_upsert_client)
	advcpp::DataStorage manager;
	advcpp::Client client("68978", 1, 2, 3, 4, 5, 6, 7, 8, 9 , 55); 
	manager.Upsert(client);
	advcpp::Client clientCpy;
	ASSERT_THAT(manager.GetOne(client.Imsi(), clientCpy));
	manager.Upsert(client);
	manager.GetOne(client.Imsi(), clientCpy);
	ASSERT_EQUAL(clientCpy.MinutesIn(), 2);
	ASSERT_EQUAL(clientCpy.MinutesOut(), 4);
	ASSERT_EQUAL(clientCpy.MinutesInOutside(), 6);
	ASSERT_EQUAL(clientCpy.MinutesOutOutside(), 8);
	ASSERT_EQUAL(clientCpy.SmsIn(), 10);
	ASSERT_EQUAL(clientCpy.SmsOut(), 12);
	ASSERT_EQUAL(clientCpy.SmsInOutside(), 14);
	ASSERT_EQUAL(clientCpy.SmsOutOutside(), 16);
	ASSERT_EQUAL(clientCpy.Download(), 18);
	ASSERT_EQUAL(clientCpy.Upload(), 110);
END_UNIT

UNIT(processor_manager_drain_client)
	const size_t size = 5;
	advcpp::DataStorage manager;
	const char* arr[] = {"123", "456", "999", "3333", "5697"};
	for(size_t i = 0; i < size; ++i)
	{
		manager.Upsert(advcpp::Client(std::string(arr[i]), i, i, i, i, i, i, i, i, i , i));
	}

	std::vector<advcpp::Client> clients;
	manager.Drain(clients);
	ASSERT_EQUAL(clients.size(), size);
END_UNIT

UNIT(convert_cdr_of_call_to_two_client_in_and_out)
	advcpp::Cdr cdr;
	cdr.m_type = advcpp::CALL;
	strcpy(cdr.m_imsi, "123456789123456");
	strcpy(cdr.m_msisdn, "5");
	strcpy(cdr.m_imei, "5");
	strcpy(cdr.m_mccMnc, "40520");
	strcpy(cdr.m_date, "date");
	strcpy(cdr.m_time, "125");
	strcpy(cdr.m_duration, "1234");
	strcpy(cdr.m_download, "0");
	strcpy(cdr.m_upload, "0");
	strcpy(cdr.m_msisdnDes, "3254588");
	strcpy(cdr.m_mccMncDes, "40520");
    strcpy(cdr.m_operatorName, "Golan");
	advcpp::Client clientOut;
	advcpp::Client::CdrToClientOut(cdr, clientOut);
	ASSERT_EQUAL(clientOut.MinutesOut(), 1234);
	advcpp::Client clientIn;
	ASSERT_THAT(advcpp::Client::CdrToClientIn(cdr, clientIn));
	ASSERT_EQUAL(clientIn.MinutesIn(), 1234);
	clientIn+=clientOut;
	ASSERT_EQUAL(clientIn.MinutesIn(), 1234 );
	ASSERT_EQUAL(clientIn.MinutesOut(), 1234);
END_UNIT

UNIT(convert_cdr_of_call_to_two_operators_in_and_out)
	advcpp::Cdr cdr;
	cdr.m_type = advcpp::CALL;
	strcpy(cdr.m_imsi, "123456789123456");
	strcpy(cdr.m_msisdn, "5");
	strcpy(cdr.m_imei, "5");
	strcpy(cdr.m_mccMnc, "105200");
	strcpy(cdr.m_date, "date");
	strcpy(cdr.m_time, "125");
	strcpy(cdr.m_duration, "2121");
	strcpy(cdr.m_download, "0");
	strcpy(cdr.m_upload, "0");
	strcpy(cdr.m_msisdnDes, "3254588");
	strcpy(cdr.m_mccMncDes, "40520");
    strcpy(cdr.m_operatorName, "Arrrrr");
	advcpp::Operator opIn;
	ASSERT_THAT(advcpp::Operator::CdrToOperatorIn(cdr, opIn));
	ASSERT_EQUAL(opIn.MinutesIn(), 2121);
	ASSERT_EQUAL(opIn.Brand(), "");
	ASSERT_EQUAL(opIn.MccMnc(), 40520);
	advcpp::Operator opOut;
	ASSERT_THAT(advcpp::Operator::CdrToOperatorOut(cdr, opOut));
	ASSERT_EQUAL(opOut.MinutesOut(), 2121);
	ASSERT_EQUAL(opOut.Brand(), "Arrrrr");
	ASSERT_EQUAL(opOut.MccMnc(), 105200);
	opIn += opOut;
	ASSERT_EQUAL(opIn.MinutesIn(), 2121);
	ASSERT_EQUAL(opIn.MinutesOut(), 2121);
END_UNIT

UNIT(convert_cdr_of_gprs_to_client_and_operator)
	advcpp::Cdr cdr;
	cdr.m_type = advcpp::GPRS;
	strcpy(cdr.m_imsi, "123456789123456");
	strcpy(cdr.m_msisdn, "5");
	strcpy(cdr.m_imei, "5");
	strcpy(cdr.m_mccMnc, "40520");
	strcpy(cdr.m_date, "date");
	strcpy(cdr.m_time, "125");
	strcpy(cdr.m_duration, "0");
	strcpy(cdr.m_download, "999");
	strcpy(cdr.m_upload, "777");
	strcpy(cdr.m_msisdnDes, "3254588");
	strcpy(cdr.m_mccMncDes, "40520");
    strcpy(cdr.m_operatorName, "Golan");
	advcpp::Client client;
	advcpp::Client::CdrToClientOut(cdr, client);
	ASSERT_EQUAL(client.Download(), 999);
	ASSERT_EQUAL(client.Upload(), 777);
	ASSERT_THAT(!advcpp::Client::CdrToClientIn(cdr, client));
	advcpp::Operator op;
	ASSERT_THAT(!advcpp::Operator::CdrToOperatorIn(cdr, op));
	ASSERT_THAT(!advcpp::Operator::CdrToOperatorOut(cdr, op));
END_UNIT

UNIT(data_storage_insert_cdr)
	advcpp::Cdr cdr;
	cdr.m_type = advcpp::CALL;
	strcpy(cdr.m_imsi, "123456789123456");
	strcpy(cdr.m_msisdn, "5");
	strcpy(cdr.m_imei, "5");
	strcpy(cdr.m_mccMnc, "40520");
	strcpy(cdr.m_date, "date");
	strcpy(cdr.m_time, "125");
	strcpy(cdr.m_duration, "1234");
	strcpy(cdr.m_download, "0");
	strcpy(cdr.m_upload, "0");
	strcpy(cdr.m_msisdnDes, "3254588");
	strcpy(cdr.m_mccMncDes, "40520");
    strcpy(cdr.m_operatorName, "Golan");
	advcpp::DataStorage storage;
	storage.Upsert(cdr);
	advcpp::Client client;
	ASSERT_THAT(storage.GetOne(cdr.m_imsi, client));
	ASSERT_EQUAL(client.MinutesOut(),  1234);
	ASSERT_THAT(storage.GetOne(cdr.m_msisdnDes, client));
	ASSERT_EQUAL(client.MinutesIn(),  1234);
	advcpp::Operator op;
	ASSERT_THAT(storage.GetOne(atoi(cdr.m_mccMnc), op));
	ASSERT_EQUAL(op.MccMnc(), 40520);
	ASSERT_EQUAL(op.Brand(), "Golan");

END_UNIT

UNIT(data_storage_insert_cdr_and_find_client)
	advcpp::Cdr cdr;
	cdr.m_type = advcpp::CALL;
	strcpy(cdr.m_imsi, "123456789123456");
	strcpy(cdr.m_msisdn, "5");
	strcpy(cdr.m_imei, "5");
	strcpy(cdr.m_mccMnc, "40520");
	strcpy(cdr.m_date, "date");
	strcpy(cdr.m_time, "125");
	strcpy(cdr.m_duration, "1234");
	strcpy(cdr.m_download, "0");
	strcpy(cdr.m_upload, "0");
	strcpy(cdr.m_msisdnDes, "3254588");
	strcpy(cdr.m_mccMncDes, "40520");
    strcpy(cdr.m_operatorName, "Golan");
	advcpp::DataStorage storage;
	storage.Upsert(cdr);
	std::vector<advcpp::Client> a_vec;
	std::string key(cdr.m_imsi);
	ASSERT_THAT(advcpp::DataStorage::Find(storage, a_vec, &key));
	ASSERT_EQUAL(a_vec.size(), 1);
	ASSERT_EQUAL(a_vec[0].Imsi(), cdr.m_imsi);
	ASSERT_EQUAL(a_vec[0].MinutesOut(), 1234);
END_UNIT

TEST_SUITE(the process manager on fire)
	TEST(processor_manager_upsert_client)
	TEST(processor_manager_drain_client)
	TEST(convert_cdr_of_call_to_two_client_in_and_out)
	TEST(convert_cdr_of_call_to_two_operators_in_and_out)
	TEST(convert_cdr_of_gprs_to_client_and_operator)
	TEST(data_storage_insert_cdr)
	TEST(data_storage_insert_cdr_and_find_client)
END_SUITE


