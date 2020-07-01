#include "hub_logger.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace smarthome
{

inline HubLogger::HubLogger(string a_fileName, Mutex & a_mutex)
: m_fileName(a_fileName)
, m_mutex(a_mutex)
{
}

// template<typename T>
// void HubLogger::Log(const T & a_t)
// {
//     {
//         Guard guard(m_mutex);
        
//         // std::stringstream ss;
//         // ss << a_t;
//         // std::string ostring = ss.str();
//         std::ofstream logFile;
//         logFile.open (m_fileName, std::ios_base::app);
//         logFile << a_t;
//         logFile.close();
//     }
// }

template<typename T>
void operator << (HubLogger & a_hubLogger, const T & a_t)
{
    a_hubLogger.Log(a_t);
}

} // namespace smarthome
