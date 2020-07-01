#include "conditional_variable.hpp"
#include <errno.h>
#include <unistd.h>

namespace advcpp
{
ConditionalVariable::ConditionalVariable() THROW1(CondVarException)
{
    int errnoTmp;
    errnoTmp = EAGAIN;
    size_t n = 3;

    while(EAGAIN == errnoTmp && n > 0)
    {
       errnoTmp = pthread_cond_init(&m_cond, 0);
       --n;
       sleep(1); 
    }

    if(errnoTmp)
    {
        throw CondVarException(errnoTmp, XINFO);
    }
}
} // namespace advcpp
