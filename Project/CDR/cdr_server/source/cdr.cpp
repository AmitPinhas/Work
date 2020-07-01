#include "cdr.hpp"

namespace advcpp
{
std::ostream& operator<<(std::ostream& a_os, const Cdr& a_cdr)
{
    return a_cdr.Print(a_os);
}

std::ostream& Cdr::Print(std::ostream& a_os) const
{
    a_os << "type " << static_cast<int>(m_type) << '\n';
    a_os << "imsi " << m_imsi << '\n';
    a_os << "msisdn " << m_msisdn << '\n';
    a_os << "imei " << m_imei << '\n';
    a_os << "mccMnc " << m_mccMnc << '\n'; 
    a_os << "date " << m_date << '\n';   
    a_os << "time " << m_time << '\n';   
    a_os << "duration " << m_duration << '\n';  
    a_os << "download " << m_download << '\n';  
    a_os << "upload " << m_upload << '\n';           
    a_os << "msisdnDes " << m_msisdnDes << '\n';   
    a_os << "mccMncDes " << m_mccMncDes << '\n';
    a_os << "length " << static_cast<int>(m_length) << '\n'; 
    a_os << "operatorName " << m_operatorName << '\n';         
    return a_os;
}
} // namespace