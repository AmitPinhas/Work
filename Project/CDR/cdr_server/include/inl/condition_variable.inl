#ifndef CONDITION_VARIABLE_INL
#define CONDITION_VARIABLE_INL

namespace advcpp
{

template<typename Predicate>
void ConditionVariable::Wait(Mutex& a_mutex, Predicate const & a_pred) THROW(ConditionVariableException)
{
    while(a_pred())
    {
        wait(a_mutex);
    }   
}

}//namespace advcpp

#endif //CONDITION_VARIABLE_INL