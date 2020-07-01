#ifndef PROTOCOL_READER_HPP
#define PROTOCOL_READER_HPP

#include <cstddef> // size_t
#include "cdr.hpp"

namespace advcpp
{
struct ProtocolReader
{
    static int ProtocolUnpackCall(Cdr* a_cdr, const char* a_msg);
    static int ProtocolUnpackSms(Cdr* a_cdr, const char* a_msg);
    static int ProtocolUnpackData(Cdr* a_cdr, const char* a_msg);
    static int ProtocolPackCall(char* a_msg, Cdr* a_cdr);
    static int ProtocolPackSms(char* a_msg, Cdr* a_cdr);
    static int ProtocolPackData(char* a_msg, Cdr* a_cdr);   

private:
    static const size_t TYPE_SIZE = 1;
    static const size_t IMSI_SIZE = 15;    
    static const size_t MSISDN_SIZE = 15;     
    static const size_t IMEI_SIZE = 15; 
    static const size_t MCC_MNC_SIZE = 6;        
    static const size_t DATE_SIZE = 10;
    static const size_t TIME_SIZE = 8;
    static const size_t DURATION_SIZE = 4;        
    static const size_t LENGTH_SIZE = 1;   
    static const size_t DOWNLOAD_SIZE = 3;
    static const size_t UPLOAD_SIZE = 3;     
};
} // namespace advcpp

#endif // PROTOCOL_READER_HPP
