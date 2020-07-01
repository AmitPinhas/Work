#ifndef CDR_HPP
#define CDR_HPP

#include <ostream> // ostream

namespace advcpp
{
enum Types
{
    CALL = 1,
    SMS,
    GPRS
};
struct Cdr
{
    char m_type;
    char m_imsi[16];
    char m_msisdn[16];
    char m_imei[16];
    char m_mccMnc[7];
    char m_date[11];
    char m_time[9]; 
    char m_duration[5]; 
    char m_download[4];
    char m_upload[4];
    char m_msisdnDes[16];
    char m_mccMncDes[7];
    char m_length;
    char m_operatorName[65];

    std::ostream& Print(std::ostream& a_os) const;
};    

std::ostream& operator<<(std::ostream& a_os, const Cdr& a_cdr);

} // namespace advcpp

#endif // CDR_HPP