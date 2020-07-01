#ifndef EXPRESSIONS_INL
#define EXPRESSIONS_INL

#include <sstream> // std::ostringstream

namespace advcpp
{

template <typename T>
BinaryExp<T>::BinaryExp(IExpressionPtr a_lhsExpressionPtr, IExpressionPtr a_rhsExpressionPtr, IOperatorPtr a_operatorPtr)
: m_lhsExpressionPtr(a_lhsExpressionPtr)
, m_rhsExpressionPtr(a_rhsExpressionPtr)
, m_operatorPtr(a_operatorPtr)
, m_value((*a_operatorPtr)(a_lhsExpressionPtr, m_rhsExpressionPtr))
{
}

template <typename T>
void BinaryExp<T>::Traverse(const ILogic<T> & a_logic) const
{
    a_logic.Execute(*this);
}

template <typename T>
std::tr1::shared_ptr<IExpression<T> > BinaryExp<T>::Left() const
{
    return m_lhsExpressionPtr;
}

template <typename T>
std::tr1::shared_ptr<IExpression<T> > BinaryExp<T>::Right() const
{
    return m_rhsExpressionPtr;
}

template <typename T>
std::string BinaryExp<T>::ToString() const
{
    return m_operatorPtr->ToString();
}

template <typename T>
T BinaryExp<T>::Value() const
{
    return m_value;
}

template <typename T>
Num<T>::Num(T a_num)
: m_num(a_num)
{
}

template <typename T>
T Num<T>::Value() const
{
    return m_num;
}

template <typename T>
void Num<T>::Traverse(const ILogic<T> & a_logic) const
{
    a_logic.Execute(*this);
}

template <typename T>
std::tr1::shared_ptr<IExpression<T> > Num<T>::Left() const
{
    std::tr1::shared_ptr<IExpression<T> > nullPtr;
    return nullPtr;
}

template <typename T>
std::tr1::shared_ptr<IExpression<T> > Num<T>::Right() const
{
    std::tr1::shared_ptr<IExpression<T> > nullPtr;
    return nullPtr;
}

template <typename T>
std::string Num<T>::ToString() const
{
    return numToString();
}

template <typename T>
std::string Num<T>::numToString() const
{
    std::ostringstream strs;
    strs << m_num << " ";
    return strs.str();
}

template <typename T>
BinaryExp<T>::~BinaryExp() NOEXCEPT
{
}

} // namespace advcpp

#endif // EXPRESSIONS_INL
