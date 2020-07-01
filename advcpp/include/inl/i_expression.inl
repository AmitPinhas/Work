#ifndef I_EXPRESSION_INL
#define I_EXPRESSION_INL

namespace advcpp
{

template <typename T>    
IExpression<T>::~IExpression() NOEXCEPT
{   
}

template <typename T>  
IExpression<T>::IExpression()
{
}

template <typename T>  
IExpression<T>::IExpression(const IExpression& a_rhs)
{
}

template <typename T>  
IExpression<T>& IExpression<T>::operator=(const IExpression& a_rhs)
{
}

} // namespace advcpp

#endif // I_EXPRESSION_INL