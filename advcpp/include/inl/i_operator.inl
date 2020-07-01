#ifndef I_OPERATOR_INL
#define I_OPERATOR_INL

namespace advcpp
{

template <typename T>    
IOperator<T>::~IOperator() NOEXCEPT
{   
}

template <typename T>  
IOperator<T>::IOperator()
{
}

template <typename T>  
IOperator<T>::IOperator(const IOperator& a_rhs)
{
}

template <typename T>  
IOperator<T>& IOperator<T>::operator=(const IOperator& a_rhs)
{
}

} // namespace advcpp

#endif // I_OPERATOR_INL