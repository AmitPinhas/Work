#include "conditional_variable.hpp"

#include "common.hpp" // uncopyable
#include "mutex.hpp" // Mutex
#include "exeption.hpp"// exeptions


namespace advcpp
{

CondVar::CondVar() THROW1(CondVarExeption)
{
    unsigned int i = 0;
    int retVal;
    do
    {
        if ( (retVal = pthread_cond_init(&m_condition, NULL) ) == 0)
        {
            return;
        }
        Nano timeToWeit(i * MiliSeconds);
        Sleep(timeToWeit);
        ++i;
    }
    while (( retVal == EAGAIN || retVal == ENOMEM ) && i < 3);
    XTHROW(CondVarExeption, "condVar was not created");
}


}//advcpp namespace