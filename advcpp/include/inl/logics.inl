#ifndef LOGICS_INL
#define LOGICS_INL

#include "logics.hpp"

namespace advcpp
{

template <typename T>
PostOrder<T>::PostOrder(ILogic<T>& a_logic)
: m_logic(a_logic)
{
}

template <typename T>
void PostOrder<T>::Execute(const IExpression<T>& a_expression) const
{   
    if(a_expression.Left())
    {
        a_expression.Left()->Traverse(*this);
    }
    if(a_expression.Right())
    {
        a_expression.Right()->Traverse(*this);
    }
    m_logic.Execute(a_expression);
}

template <typename T>
InOrder<T>::InOrder(ILogic<T>& a_logic)
: m_logic(a_logic)
{
}

template <typename T>
void InOrder<T>::Execute(const IExpression<T>& a_expression) const
{   
    if(a_expression.Left())
    {
        a_expression.Left()->Traverse(*this);
    }

    m_logic.Execute(a_expression);

    if(a_expression.Right())
    {
        a_expression.Right()->Traverse(*this);
    }
}

template <typename T>
PreOrder<T>::PreOrder(ILogic<T>& a_logic)
: m_logic(a_logic)
{
}

template <typename T>
void PreOrder<T>::Execute(const IExpression<T>& a_expression) const
{   
    m_logic.Execute(a_expression);

    if(a_expression.Left())
    {
        a_expression.Left()->Traverse(*this);
    }

    if(a_expression.Right())
    {
        a_expression.Right()->Traverse(*this);
    }
}

template <typename T>
Printer<T>::Printer(std::ostream& a_os)
: m_os(a_os)
{
}

template <typename T>
void Printer<T>::Execute(const IExpression<T>& a_expression) const
{
    m_os << a_expression.ToString();
}

} // namespace advcpp

#endif // LOGICS_INL