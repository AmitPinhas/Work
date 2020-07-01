#include "hub_logger.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace smarthome
{

void HubLogger::Log(const fstream & a_fstream)
{
    {
        Guard guard(m_mutex);
            (void)a_fstream;
        // std::ofstream logFile;
        // logFile.open (m_fileName, std::ios_base::app);
        // logFile << a_fstream;
        // logFile.close();
    }

}


} // namespace smarthome
