#include "mutex.hpp"


namespace advcpp
{


Mutex::~Mutex() NO_EXEPTION
{
    pthread_mutex_destroy(&m_mutex);
}

}//end advcpp namespace