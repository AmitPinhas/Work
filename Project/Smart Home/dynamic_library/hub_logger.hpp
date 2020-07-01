#ifndef HUB_LOGGER_H
#define HUB_LOGGER_H

#include "mutex.hpp"
#include <iostream>

using namespace std;
using namespace advcpp;

namespace smarthome
{

class HubLogger
{
public:
    
    HubLogger(string a_fileName, Mutex & a_mutex);
    ~HubLogger() = default;
    HubLogger(const HubLogger & a_hubLogger) = delete;
    HubLogger & operator = (const HubLogger & a_hubLogger) = delete;

    void Log(const fstream & a_fstream);

private:
    string m_fileName;
    Mutex & m_mutex;
};

template<typename T>
void operator << (HubLogger & a_hubLogger, const T & a_t);


} // namespace smarthome

#include "inl/hub_logger.inl"

#endif // HUB_LOGGER_H