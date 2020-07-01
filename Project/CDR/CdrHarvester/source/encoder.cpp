#include "encoder.hpp"
#include <iostream>
#include <string.h>

#include "protocol_reader.hpp"
#include "protocol.hpp"
#include "cdr.hpp"

namespace advcpp
{

bool Encoder::MakeMsg(char* a_buffer, std::string const& a_line)
{
    cpp::Parser pars('|');
    std::vector<std::string> fields;

    pars.GetRecord(a_line, fields);

    if (fields.size() != NoFields)
    {
        return false;
    }

    Cdr tempCdr;
    if (fields[5] == "moc" || fields[5] == "mtc")
    {
        MakeCdrCall(fields, tempCdr);
        ProtocolReader::ProtocolPackCall(a_buffer, &tempCdr);
        return true;
    }
    else if (fields[5] == "sms-mo" || fields[5] == "sms-mt")
    {
        MakeCdrSms(fields, tempCdr);
        ProtocolReader::ProtocolPackSms(a_buffer, &tempCdr);
        return true;
    }
    else if (fields[5] == "gprs")
    {
        MakeCdrGprs(fields, tempCdr);
        ProtocolReader::ProtocolPackData(a_buffer, &tempCdr);
        return true;
    }
    else
    {
        return false;
    }
    
}

void Encoder::MakeCdrCall(std::vector<std::string>const& a_parsed, Cdr& a_cdr)
{
    a_cdr.m_length = strlen(a_parsed[3].c_str());
    strcpy(a_cdr.m_imsi , &a_parsed[0][0]);
    strcpy(a_cdr.m_msisdn , &a_parsed[1][0]);
    strcpy(a_cdr.m_imei , &a_parsed[2][0]);
    strcpy(a_cdr.m_operatorName , &a_parsed[3][0]);
    strcpy(a_cdr.m_mccMnc , &a_parsed[4][0]);
    a_cdr.m_type = 1;
    strcpy(a_cdr.m_date , &a_parsed[6][0]);
    strcpy(a_cdr.m_time , &a_parsed[7][0]);
    strcpy(a_cdr.m_duration , &a_parsed[8][0]);
    strcpy(a_cdr.m_msisdnDes , &a_parsed[11][0]);
    strcpy(a_cdr.m_mccMncDes , &a_parsed[12][0]);
}

void Encoder::MakeCdrSms(std::vector<std::string>const& a_parsed, Cdr& a_cdr)
{
    a_cdr.m_length = strlen(a_parsed[3].c_str());
    strcpy(a_cdr.m_imsi , &a_parsed[0][0]);
    strcpy(a_cdr.m_msisdn , &a_parsed[1][0]);
    strcpy(a_cdr.m_imei , &a_parsed[2][0]);
    strcpy(a_cdr.m_operatorName , &a_parsed[3][0]);
    strcpy(a_cdr.m_mccMnc , &a_parsed[4][0]);
    a_cdr.m_type = 2;
    strcpy(a_cdr.m_date , &a_parsed[6][0]);
    strcpy(a_cdr.m_time , &a_parsed[7][0]);
    strcpy(a_cdr.m_msisdnDes , &a_parsed[11][0]);
    strcpy(a_cdr.m_mccMncDes , &a_parsed[12][0]);
}

void Encoder::MakeCdrGprs(std::vector<std::string>const& a_parsed, Cdr& a_cdr)
{
    a_cdr.m_length = strlen(a_parsed[3].c_str());
    strcpy(a_cdr.m_imsi , &a_parsed[0][0]);
    strcpy(a_cdr.m_msisdn , &a_parsed[1][0]);
    strcpy(a_cdr.m_imei , &a_parsed[2][0]);
    strcpy(a_cdr.m_operatorName , &a_parsed[3][0]);
    strcpy(a_cdr.m_mccMnc , &a_parsed[4][0]);
    a_cdr.m_type = 3;
    strcpy(a_cdr.m_date , &a_parsed[6][0]);
    strcpy(a_cdr.m_time , &a_parsed[7][0]);
    strcpy(a_cdr.m_download , &a_parsed[9][0]);
    strcpy(a_cdr.m_upload , &a_parsed[10][0]);
}




}//advcpp namespace