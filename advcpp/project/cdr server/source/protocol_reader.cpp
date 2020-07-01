#include "protocol_reader.hpp"

#include <string.h> // memcpy

namespace advcpp
{
int ProtocolReader::ProtocolUnpackCall(Cdr* a_cdr, const char* a_msg)
{
    int loc = 0;

    memcpy((void*) &a_cdr->m_type, (void*) &a_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_cdr->m_imsi, (void*) &a_msg[loc], IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_cdr->m_msisdn, (void*) &a_msg[loc], MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_cdr->m_imei, (void*) &a_msg[loc], IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_cdr->m_mccMnc, (void*) &a_msg[loc], MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_cdr->m_date, (void*) &a_msg[loc], DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_cdr->m_time, (void*) &a_msg[loc], TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_cdr->m_duration, (void*) &a_msg[loc], DURATION_SIZE);
    loc += DURATION_SIZE;
    memcpy((void*) &a_cdr->m_msisdnDes, (void*) &a_msg[loc], MSISDN_SIZE);
    loc += MSISDN_SIZE;   
    memcpy((void*) &a_cdr->m_mccMncDes, (void*) &a_msg[loc], MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE; 
    memcpy((void*) &a_cdr->m_length, (void*) &a_msg[loc], LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_cdr->m_operatorName, (void*) &a_msg[loc], (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;    
}

int ProtocolReader::ProtocolPackCall(char* a_msg, Cdr* a_cdr)
{
    int loc = 0;

    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_type, TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imsi, IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_msisdn, MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imei, IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_mccMnc, MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_date, DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_time, TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_duration, DURATION_SIZE);
    loc += DURATION_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_msisdnDes, MSISDN_SIZE);
    loc += MSISDN_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_mccMncDes, MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE; 
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_length, LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_operatorName, (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;        
}

int ProtocolReader::ProtocolUnpackSms(Cdr* a_cdr, const char* a_msg)
{
    int loc = 0;

    memcpy((void*) &a_cdr->m_type, (void*) &a_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_cdr->m_imsi, (void*) &a_msg[loc], IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_cdr->m_msisdn, (void*) &a_msg[loc], MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_cdr->m_imei, (void*) &a_msg[loc], IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_cdr->m_mccMnc, (void*) &a_msg[loc], MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_cdr->m_date, (void*) &a_msg[loc], DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_cdr->m_time, (void*) &a_msg[loc], TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_cdr->m_msisdnDes, (void*) &a_msg[loc], MSISDN_SIZE);
    loc += MSISDN_SIZE;   
    memcpy((void*) &a_cdr->m_mccMncDes, (void*) &a_msg[loc], MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE; 
    memcpy((void*) &a_cdr->m_length, (void*) &a_msg[loc], LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_cdr->m_operatorName, (void*) &a_msg[loc], (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;   
}

int ProtocolReader::ProtocolPackSms(char* a_msg, Cdr* a_cdr)
{
    int loc = 0;

    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_type, TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imsi, IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_msisdn, MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imei, IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_mccMnc, MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_date, DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_time, TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_msisdnDes, MSISDN_SIZE);
    loc += MSISDN_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_mccMncDes, MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE; 
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_length, LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_operatorName, (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;     
}

int ProtocolReader::ProtocolUnpackData(Cdr* a_cdr, const char* a_msg)
{
    int loc = 0;

    memcpy((void*) &a_cdr->m_type, (void*) &a_msg[loc], TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_cdr->m_imsi, (void*) &a_msg[loc], IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_cdr->m_msisdn, (void*) &a_msg[loc], MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_cdr->m_imei, (void*) &a_msg[loc], IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_cdr->m_mccMnc, (void*) &a_msg[loc], MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_cdr->m_date, (void*) &a_msg[loc], DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_cdr->m_time, (void*) &a_msg[loc], TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_cdr->m_download, (void*) &a_msg[loc], DOWNLOAD_SIZE);
    loc += DOWNLOAD_SIZE;
    memcpy((void*) &a_cdr->m_upload, (void*) &a_msg[loc], UPLOAD_SIZE);
    loc += UPLOAD_SIZE;   
    memcpy((void*) &a_cdr->m_length, (void*) &a_msg[loc], LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_cdr->m_operatorName, (void*) &a_msg[loc], (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;            
}

int ProtocolReader::ProtocolPackData(char* a_msg, Cdr* a_cdr)
{
    int loc = 0;

    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_type, TYPE_SIZE);
    loc += TYPE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imsi, IMSI_SIZE);
    loc += IMSI_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_msisdn, MSISDN_SIZE);
    loc += MSISDN_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_imei, IMEI_SIZE);
    loc += IMEI_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_mccMnc, MCC_MNC_SIZE);
    loc += MCC_MNC_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_date, DATE_SIZE);
    loc += DATE_SIZE;
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_time, TIME_SIZE);
    loc += TIME_SIZE;  
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_download, DOWNLOAD_SIZE);
    loc += DOWNLOAD_SIZE;   
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_upload, UPLOAD_SIZE);
    loc += UPLOAD_SIZE; 
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_length, LENGTH_SIZE);
    loc += LENGTH_SIZE;    
    memcpy((void*) &a_msg[loc], (void*) &a_cdr->m_operatorName, (size_t) a_cdr->m_length);
    loc += (size_t) a_cdr->m_length;                                   
    return loc;       
}   
} // namespace advcpp
